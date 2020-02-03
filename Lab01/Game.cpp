//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include <iostream>

// TODO
Game::Game() {}

bool Game::Initialize(){
    
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        return false;
    }
    //SDL_Quit();
    myWindow = SDL_CreateWindow(
        "The Pong Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_width,
        window_height,
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
    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN]) {
        if (state[SDL_SCANCODE_UP]) {
            direction = 1;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            direction = 2;
        }
    } else {
        direction = 0;
    }
    
}

void Game::RunLoop(){
    while(runLoop){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::MakeARect(SDL_Rect rect, SDL_Renderer* renderer,
               int x1, int y1, int w1, int h1){
    rect.x = x1;
    rect.y = y1;
    rect.w = w1;
    rect.h = h1;
    SDL_RenderFillRect(renderer, &rect);
}

void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(myRenderer, 0, 0, 255, 255);
    SDL_RenderClear(myRenderer);
    
    SDL_SetRenderDrawColor(myRenderer, 255, 255, 255, 255);
    SDL_Rect top_wall{0, 0, window_width, wall_thickness};
    SDL_Rect side_wall{side_wall_x, 0, wall_thickness, window_height};
    SDL_Rect bottom_wall{0, side_wall_y, window_width, window_height};
    
    MakeARect(top_wall, myRenderer, 0, 0, window_width, wall_thickness);
    MakeARect(side_wall, myRenderer, side_wall_x, 0, wall_thickness, window_height);
    MakeARect(bottom_wall, myRenderer, 0, side_wall_y, window_width, wall_thickness);
    
    MakeARect(paddle, myRenderer, 15, paddle.y, paddle_width, paddle_height);
    
    MakeARect(ball, myRenderer, ballPosition.x, ballPosition.y, ball_size, ball_size);
    
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
    
    //moving the paddle
    if (direction == 1){
        if(paddle.y > top_wall_boundary){
            paddle.y = paddle.y - (int)(PADDLE_SPEED * delta_time);
        }
    }
    if (direction == 2){
        if(paddle.y < bottom_wall_boundary){
            paddle.y = paddle.y + (int)(PADDLE_SPEED * delta_time);
        }
    }
    
    //collisions
    if(ballPosition.y <= top_wall_limit){
        ballPosition.y = top_wall_offset;
        ballVelocity.y = -ballVelocity.y;
    }
    if(ballPosition.y >= bottom_wall_limit) {
         ballPosition.y = bottom_wall_offset;
        ballVelocity.y = -ballVelocity.y;
    }
    if(ballPosition.x >= side_wall_limit){
        ballPosition.x =side_wall_offset;
        ballVelocity.x = -ballVelocity.x;
    }

    if((ballPosition.x <= top_wall_boundary) && (paddle.y <= ballPosition.y) && (ballPosition.y < paddle.y+100)){
        ballPosition.x = top_wall_limit;
        ballVelocity.x = -ballVelocity.x;
    }
    
    //player loses
    if(ballPosition.x <= ball_out_of_bounds){
        ballVelocity.x = -ballVelocity.x;
        runLoop = false;
    }
    
    //ball moves
    ballPosition.x = ballPosition.x + (int)(ballVelocity.x * delta_time);
    ballPosition.y = ballPosition.y + (int)(ballVelocity.y * delta_time);
    
    
}
