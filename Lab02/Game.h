#pragma once
#include "SDL2/SDL.h"
#include <iostream>
#include <vector>
// TODO
class Game {
    public:
    
        //constructor
        Game();
    
        //member variables
        SDL_Window* myWindow;
        SDL_Renderer* myRenderer;
    
        bool runLoop = true;
    
        Uint32 current_time;
        Uint32 previous_time = 0;
        float delta_time;
    
        int direction = 0;
    
        //functions
        bool Initialize();
        void Shutdown();
        void RunLoop();
    
        void ProcessInput();
        void UpdateGame();
        void GenerateOutput();
    
        //Actor
    
        //forward declaration
        class Actor* mActor;
        
        std::vector<class Actor*> mActors;
    
        //functions
        void AddActor(Actor* actor);
        void RemoveActor(Actor* actor);
        
};


