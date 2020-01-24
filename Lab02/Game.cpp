//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include <iostream>
#include <vector>
#include <algorithm>

// TODO
Game::Game() {}

bool Game::Initialize(){
    
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        return false;
    }
    //SDL_Quit();
    myWindow = SDL_CreateWindow(
        "The Asteroid Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        SDL_WINDOW_OPENGL
    );
    
    myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    return true;
}

void Game::Shutdown(){
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
            actorsTemp->AddActor(mActors[i]);
        }
    }
}

//Actor

void Game::AddActor(Actor* actor){
    mActors.push_back(mActor);
}

void Game::RemoveActor(Actor* actor){
    auto it = std::find(mActors.begin(), mActors.end(), actor);
    if(it != mActors.end())
    {
        mActors.erase(it);
    }
}
