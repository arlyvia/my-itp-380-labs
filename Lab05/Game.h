#pragma once
#include "SDL2/SDL.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include "Math.h"
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
    
        const int start_offset_x = 16;
        const int start_offset_y = 16;
    
        //Player
        class Player* mPlayer;

        //camera
        Vector2 camera_pos;
    
        //sound
        std::unordered_map<std::string, Mix_Chunk*> soundMap;
        Mix_Chunk* GetSound(const std::string& filename);
    
        int mChannel;
    
        //csv
    
        std::vector<std::vector<std::string>> readObjectCSV(std::string filename);
        std::vector<std::vector<std::string>> obj_csv_storage;
    
        //colliders
        void loadPlayersAndColliders(std::string room);
    
        std::vector<class Collider*> mColliders;
    
        //doors
        std::unordered_map<std::string, std::vector<class Door*>> doorMap;
        std::string currRoom;
        
    private:
    
        void LoadData();
        void UnloadData();
};


