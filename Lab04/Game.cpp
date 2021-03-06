//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Player.hpp"
#include "Block.hpp"
#include "Goomba.hpp"
#include "Spawner.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <string>
#include <SDL2/SDL_image.h>

// TODO
Game::Game() {}

bool Game::Initialize(){
    
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        return false;
    }
    //SDL_Quit();
    myWindow = SDL_CreateWindow(
        "The Mario Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        600,
        448,
        SDL_WINDOW_OPENGL
    );
    
    myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    IMG_Init(IMG_INIT_PNG);
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    
    LoadData();
    
    return true;
}

void Game::Shutdown(){
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(myRenderer);
    SDL_DestroyWindow(myWindow);
    SDL_Quit();
    Mix_CloseAudio();
}

void Game::ProcessInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                runLoop = false;
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        runLoop = false;
    }
    
    std::vector<class Actor*> actorsCopy = mActors;
    
    for(int i = 0; i < (int)(actorsCopy.size()); i++){
        actorsCopy[i]->ProcessInput(state);
    }
    
}

void Game::RunLoop(){
    while(runLoop){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}


void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(myRenderer, 0, 0, 225, 255);
    SDL_RenderClear(myRenderer);
    for(int i = 0; i < (int)(mSprites.size()); i++){
        if(mSprites[i]->IsVisible()) mSprites[i]->Draw(myRenderer);
    }
    SDL_RenderPresent(myRenderer);
}

void Game::UpdateGame(){
    while(SDL_GetTicks() < previous_time+16){}
    current_time = SDL_GetTicks();
    
    delta_time = (current_time - previous_time)/1000.0f; // 0.01666f (60FPS), 0.03333f (30FPS)
    previous_time = current_time;
    
    if(delta_time > 0.033f){
        delta_time = 0.033f;
    }
    
    std::vector<class Actor*> actorsCopy = mActors;
    
    for(int i = 0; i < (int)(actorsCopy.size()); i++){
        actorsCopy[i]->Update(delta_time);
    }

    std::vector<class Actor*> actorsTemp;
    
    for(int i = 0; i < (int)(mActors.size()); i++){
        if(mActors[i]->GetState() == ActorState::Destroy){
            actorsTemp.push_back(mActors[i]);
        }
    }
    
    for(auto& actor : actorsTemp)
    {
        delete actor;
    }
}

//Actor

void Game::AddActor(Actor* actor){
    mActors.push_back(actor);
}

void Game::RemoveActor(Actor* actor){
    auto it = std::find(mActors.begin(), mActors.end(), actor);
    if(it != mActors.end())
    {
        mActors.erase(it);
    }
}

void Game::LoadData(){
   Actor* bg = new Actor(this);
   SpriteComponent* bg_sc = new SpriteComponent(bg);
   bg_sc->SetTexture(GetTexture("Assets/Background.png"));
   bg_sc->SetDrawOrder(100);
   Vector2 pos_bg = Vector2(3392, 224);
   bg->SetPosition(pos_bg);
    
   readTextFile("Assets/Level1.txt");
    Mix_Chunk* music = GetSound("Assets/Sounds/Music.ogg");
    mChannel = Mix_PlayChannel(-1, music, -1);
    if(mChannel==-1) {
        printf("Mix_PlayChannel: %s\n",Mix_GetError());
    }
    
}

void Game::UnloadData(){
    while(mActors.size() > 0) {
        delete mActors.back();
    }
    
    for ( auto it = textureMap.begin(); it != textureMap.end(); ++it ){
        SDL_DestroyTexture(it->second);
    }
    
    for ( auto it = soundMap.begin(); it != soundMap.end(); ++it ){
        Mix_FreeChunk(it->second);
        it->second=nullptr;
    }
}

SDL_Texture* Game::GetTexture(std::string filename){
    std::unordered_map<std::string,SDL_Texture*>::const_iterator got = textureMap.find (filename);

    if ( got == textureMap.end() ){
         SDL_Surface* image = IMG_Load(filename.c_str());
         SDL_Texture *texture = SDL_CreateTextureFromSurface(myRenderer, image);
         SDL_FreeSurface(image);
        if(image != nullptr){
            textureMap[filename] = texture;
        } else {
            SDL_Log("Failed to load : ");
            SDL_Log(filename.c_str());
            return 0;
        }
        return texture;
    } else {
        return got->second;
    }
}

//Sprites

void Game::AddSprite(SpriteComponent* sprite){
    mSprites.push_back(sprite);
    std::sort(mSprites.begin(), mSprites.end(),
              [](SpriteComponent* a, SpriteComponent* b) {
                    return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void Game::RemoveSprite(SpriteComponent* sprite){
    auto it = std::find(mSprites.begin(), mSprites.end(), sprite);
    if(it != mSprites.end())
    {
        mSprites.erase(it);
    }
}

//Blocks
void Game::AddBlock(Block* block){
    mBlocks.push_back(block);
}

void Game::RemoveBlock(Block* block){
    auto it = std::find(mBlocks.begin(), mBlocks.end(), block);
    if(it != mBlocks.end())
    {
        mBlocks.erase(it);
    }
}

void Game::createBlock(std::string texture, int pos_i, int pos_j){
        Block* blockA = new Block(this);
        SpriteComponent* blockA_sc = new SpriteComponent(blockA);
        blockA_sc->SetTexture(GetTexture(texture));
        Vector2 pos_blockA =
            Vector2(start_offset_x + pos_j*32,
            start_offset_y + pos_i*32);
        blockA->SetPosition(pos_blockA);
    
}

void Game::createPlayer(int pos_i, int pos_j){
    mPlayer = new Player(this);
    mPlayer->SetPosition(Vector2(start_offset_x + pos_j*32,
                                 start_offset_y + pos_i*32));
}

void Game::createSpawner(int pos_i, int pos_j){
    Spawner* spawner = new Spawner(this);
    spawner->SetPosition(Vector2(start_offset_x + pos_j*32,
                                 start_offset_y + pos_i*32));
}

void Game::readTextFile(std::string filename){
    std::ifstream textFile;
    textFile.open(filename);
    if (!textFile) {
        exit(1);
    }
  
    std::string str = "";
    
    for(int i = 0; i<15; i++){
        std::getline(textFile, str);
        for(int j = 0; j<(signed)str.length(); j++){
            if(str[j] == '.'){
                continue;
            }
            if(str[j] == 'A'){
                createBlock("Assets/BlockA.png", i, j);
            }
            if(str[j] == 'B'){
                createBlock("Assets/BlockB.png", i, j);
            }
            if(str[j] == 'C'){
                createBlock("Assets/BlockC.png", i, j);
            }
            if(str[j] == 'D'){
                createBlock("Assets/BlockD.png", i, j);
            }
            if(str[j] == 'E'){
                createBlock("Assets/BlockE.png", i, j);
            }
            if(str[j] == 'F'){
                createBlock("Assets/BlockF.png", i, j);
            }
            if(str[j] == 'G'){
                createBlock("Assets/BlockG.png", i, j);
            }
            if(str[j] == 'H'){
                createBlock("Assets/BlockH.png", i, j);
            }
            if(str[j] == 'I'){
                createBlock("Assets/BlockI.png", i, j);
            }
            if(str[j] == 'P'){
                createPlayer(i, j);
            }
            if(str[j] == 'Y'){
                createSpawner(i, j);
            }
        }
    }
    
}

Mix_Chunk* Game::GetSound(const std::string& filename){
    std::unordered_map<std::string,Mix_Chunk*>::const_iterator got = soundMap.find (filename);

    if ( got == soundMap.end() ){
         /*SDL_Surface* image = IMG_Load(filename.c_str());
         SDL_Texture *texture = SDL_CreateTextureFromSurface(myRenderer, image);
         SDL_FreeSurface(image);*/
        
         Mix_Chunk *sound;
         sound = Mix_LoadWAV(filename.c_str());
        if(sound != nullptr){
            soundMap[filename] = sound;
        } else {
            SDL_Log("Mix_LoadWAV: %s/n", Mix_GetError());
            return 0;
        }
        return sound;
    } else {
        return got->second;
    }
}
