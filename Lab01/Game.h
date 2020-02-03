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
        int window_width = 1024;
        int window_height = 768;
        SDL_Renderer* myRenderer;
    
        bool runLoop = true;
    
        SDL_Rect ball;
    
        const int wall_thickness = 20;
    
        SDL_Rect paddle = {20, 384};
        SDL_Point paddlePosition = {20, 384};
    
        int paddle_width = 12;
        int paddle_height = 100;
    
        SDL_Point ballPosition = {512, 384};
        SDL_Point ballVelocity = {300, 335};
    
        int ball_out_of_bounds = -25;
    
        const float PADDLE_SPEED = 500.0f;
    
        int top_wall_boundary = 25;
        int bottom_wall_boundary = 643;
        int side_wall_x = 1004;
        int side_wall_y = 748;
    
        int top_wall_limit = 26;
        int top_wall_offset = 27;
        int bottom_wall_limit = 738;
        int bottom_wall_offset = 737;
        int side_wall_limit = 989;
        int side_wall_offset = 988;
    
        int ball_size = 12;
    
        Uint32 current_time;
        Uint32 previous_time = 0;
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


