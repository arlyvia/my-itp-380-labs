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
    
        bool runLoop;
    
        //functions
        bool Initialize();
        void Shutdown();
        void RunLoop();
    
        void ProcessInput(){
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT: runLoop = false;
                }
            }
        }
        void UpdateGame();
        void GenerateOutput();
        
};


