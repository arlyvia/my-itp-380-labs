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
#include "TiledBGComponent.hpp"
#include "Player.hpp"
#include "Spawner.hpp"
#include "CSVHelper.h"
#include "Collider.hpp"
#include "Door.hpp"
#include <utility>
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
        "The Zelda Window",
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
    SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);
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
    TiledBGComponent* bg_tc = new TiledBGComponent(bg);
    bg_tc->LoadTileCSV("Assets/Dungeon/DungeonMapBG.csv", 32, 32);
    bg_tc->SetTexture(GetTexture("Assets/Dungeon/DungeonTiles.png"));
    
    readObjectCSV("Assets/Dungeon/Room1.csv");
    currRoom = "Room1";
    loadPlayersAndColliders(currRoom);
    //std::cout << bg_tc->csv_storage[0][0] << std::endl;
    /*Mix_Chunk* music = GetSound("Assets/Sounds/Music.ogg");
    mChannel = Mix_PlayChannel(-1, music, -1);
    if(mChannel==-1) {
        printf("Mix_PlayChannel: %s\n",Mix_GetError());
    }*/
    
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

void Game::readObjectCSV(std::string filename){
    std::ifstream textFile;
    textFile.open(filename);
    if (!textFile) {
        exit(1);
    }
    std::string str = "";
    
    while(textFile){
        std::getline(textFile, str);
        if(str != ""){
            std::vector line = CSVHelper::Split(str);
            obj_csv_storage.push_back(line);
        }
    }
}

void Game::loadPlayersAndColliders(std::string room){
    std::vector<Door*> doors;
    for(int i=0; i < (int)obj_csv_storage.size(); i++){
        if(obj_csv_storage[i][0] == "Player"){
            mPlayer = new Player(this);
            std::string x_str = obj_csv_storage[i][1];
            std::string y_str = obj_csv_storage[i][2];
            mPlayer->SetPosition(Vector2(std::stoi(x_str), std::stoi(y_str)));
        }
        if(obj_csv_storage[i][0] == "Collider"){
            std::string w_str = obj_csv_storage[i][3];
            std::string h_str = obj_csv_storage[i][4];
            Collider* collider = new Collider(this, std::stoi(w_str), std::stoi(h_str));
            std::string x_str = obj_csv_storage[i][1];
            std::string y_str = obj_csv_storage[i][2];
            int x = std::stoi(x_str) + std::stoi(w_str)/2;
            int y = std::stoi(y_str) + std::stoi(h_str)/2;
            collider->SetPosition(Vector2(x, y));
            mColliders.push_back(collider);
        }
        if(obj_csv_storage[i][0] == "Door"){
            Door* door = new Door(this);
            std::string x_str = obj_csv_storage[i][1];
            std::string y_str = obj_csv_storage[i][2];
            std::string w_str = obj_csv_storage[i][3];
            std::string h_str = obj_csv_storage[i][4];
            int x = std::stoi(x_str) + std::stoi(w_str)/2;
            int y = std::stoi(y_str) + std::stoi(h_str)/2;
            door->SetPosition(Vector2(x, y));
            std::string dest = obj_csv_storage[i][5];
            std::string dir = obj_csv_storage[i][6];
            std::string state = obj_csv_storage[i][7];
            
            if(dir == "Up"){
                door->mDirection = DoorDirection::Up;
            } else if(dir == "Down"){
                door->mDirection = DoorDirection::Down;
            } else if(dir == "Left"){
                door->mDirection = DoorDirection::Left;
            } else if(dir == "Right"){
                door->mDirection = DoorDirection::Right;
            }
            
            if(state == "Closed"){
                door->mState = DoorState::Closed;
            } else if(state == "Open"){
                door->mState = DoorState::Open;
            } else if(state == "Locked"){
                door->mState = DoorState::Locked;
            }
            
            door->SetUpDoor(door->mDirection, door->mState, dest);
            doors.push_back(door);
        }
    }
    doorMap.insert({room, doors});
}
