//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"

// TODO
Game::Game() {}

bool Game::Initialize(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        return false;
    }
    //SDL_Quit();
    myWindow = SDL_CreateWindow(
        "The Pong Window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        1024,                               // width, in pixels
        768,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags
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

void Game::UpdateGame(){}

void Game::MakeARect(SDL_Rect wall, SDL_Renderer* renderer,
               int x1, int y1, int w1, int h1){
    wall.x = x1;
    wall.y = y1;
    wall.w = w1;
    wall.h = h1;
    SDL_RenderFillRect(renderer, &wall);
}

void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(myRenderer, 0, 0, 255, 255);
    SDL_RenderClear(myRenderer);
    
    SDL_SetRenderDrawColor(myRenderer, 255, 255, 255, 255);
    SDL_Rect top_wall;
    SDL_Rect side_wall;
    SDL_Rect bottom_wall;
    const int thickness = 20;
    MakeARect(top_wall, myRenderer, 0, 0, 1024, thickness);
    MakeARect(side_wall, myRenderer, 1004, 0, thickness, 768);
    MakeARect(bottom_wall, myRenderer, 0, 748, 1024, thickness);
    
    SDL_SetRenderDrawColor(myRenderer, 255, 50, 50, 255);
    SDL_Rect paddle;
    const int paddle_height = 100;
    MakeARect(paddle, myRenderer, 15, 324, 12, paddle_height);
    
    SDL_SetRenderDrawColor(myRenderer, 90, 255, 0, 255);
    SDL_Rect ball;
    const int ball_height = 15;
    MakeARect(ball, myRenderer, 512, 384, ball_height, ball_height);
    
    SDL_RenderPresent(myRenderer);
}
