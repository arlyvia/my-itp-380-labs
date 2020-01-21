#pragma once
#include "SDL2/SDL.h"
#include <iostream>

// TODO
class Game {
    public:
    
        //constructor
        Game();
    
        //member variables
        SDL_Window* myWindow;
        SDL_Renderer* myRenderer;
    
        bool runLoop = true;
    
        SDL_Rect ball;
    
        SDL_Rect paddle = {20, 384};
        SDL_Point paddlePosition = {20, 384};
    
        SDL_Point ballPosition = {512, 384};
        SDL_Point ballVelocity = {1, 1};
    
        float current_time;
        float previous_time = 0;
        float delta_time;
    
        int direction = 0;
    
        int score = 0;
    
        //functions
        bool Initialize();
        void Shutdown();
        void RunLoop();
    
        void ProcessInput();
        void UpdateGame();
        void GenerateOutput();
        
        void MakeARect(SDL_Rect rect, SDL_Renderer* renderer,
                       int x1, int y1, int w1, int h1);
};


