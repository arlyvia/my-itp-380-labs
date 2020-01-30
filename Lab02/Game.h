#pragma once
#include "SDL2/SDL.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
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
    
        //Images
        
        //hash map
        std::unordered_map<std::string, SDL_Texture*> textureMap;
    
        //functions
        SDL_Texture* GetTexture(std::string filename);
    
        //Sprites
        class SpriteComponent* mSprite;
        std::vector<class SpriteComponent*> mSprites;
    
        //functions
        void AddSprite(SpriteComponent* sprite);
        void RemoveSprite(SpriteComponent* sprite);
    
    private:
    
        void LoadData();
        void UnloadData();
};


