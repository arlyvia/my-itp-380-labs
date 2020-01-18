#pragma once
#include "SDL2/SDL.h"

// TODO
class Game {
    public:
    
        //constructor
        Game();
    
        //member variables
        SDL_Window* myWindow;
        SDL_Renderer* myRenderer;
    
        bool runLoop = true;
    
        SDL_Point paddlePosition = {20, 384};
    
        SDL_Point ballPosition = {512, 384};
    
        //functions
        bool Initialize();
        void Shutdown();
        void RunLoop();
    
        void ProcessInput();
        void UpdateGame();
        void GenerateOutput();
        
        void MakeARect(SDL_Rect wall, SDL_Renderer* renderer,
                       int x1, int y1, int w1, int h1);
};


