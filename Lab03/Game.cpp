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
#include "Paddle.hpp"
#include "Ball.hpp"
#include "BallMove.hpp"
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
        "The Blocks Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        SDL_WINDOW_OPENGL
    );
    
    myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    IMG_Init(IMG_INIT_PNG);
    
    LoadData();
    
    return true;
}

void Game::Shutdown(){
    UnloadData();
    IMG_Quit();
    SDL_DestroyRenderer(myRenderer);
    SDL_DestroyWindow(myWindow);
    SDL_Quit();
    
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
   Vector2 pos_bg = Vector2(512, 384);
   bg->SetPosition(pos_bg);
    
   readTextFile("Assets/Level.txt");
    
    mPaddle = new Paddle(this);
    Vector2 pos_paddle = Vector2(horizontal_center, paddle_pos_y);
    mPaddle->SetPosition(pos_paddle);
    
    Ball* ball = new Ball(this);
    Vector2 pos_ball = Vector2(horizontal_center, paddle_pos_y - 100);
    ball->SetPosition(pos_ball);
    BallMove* ball_mc = new BallMove(ball);
    
}

void Game::UnloadData(){
    while(mActors.size() > 0) {
        delete mActors.back();
    }
    
    for ( auto it = textureMap.begin(); it != textureMap.end(); ++it ){
        SDL_DestroyTexture(it->second);
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

void Game::createBlock(std::string texture, int pos_i, int pos_j){
        Actor* blockA = new Actor(this);
        SpriteComponent* blockA_sc = new SpriteComponent(blockA);
        blockA_sc->SetTexture(GetTexture(texture));
        Vector2 pos_blockA =
            Vector2(start_offset_x + pos_j*64 + half_of_width,
            start_offset_y + pos_i*32 + half_of_height);
        blockA->SetPosition(pos_blockA);
    
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
        for(int j = 0; j<15; j++){
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
        }
    }
    
}

