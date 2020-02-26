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
    
        //Lab3 textfile code
        void readTextFile(std::string filename);
    
        const int start_offset_x = 16;
        const int start_offset_y = 16;
    
        void createBlock(std::string texture, int pos_x, int pos_y);
    
        //Blocks
        std::vector<class Block*> mBlocks;
    
        void AddBlock(Block* block);
        void RemoveBlock(Block* block);
    
        //Player
        class Player* mPlayer;
        void createPlayer(int pos_i, int pos_j);
    
        //camera
        Vector2 camera_pos;
    
        std::vector<class Goomba*> mEnemies;
        void createSpawner(int pos_i, int pos_j);
    
        //sound
        std::unordered_map<std::string, Mix_Chunk*> soundMap;
        Mix_Chunk* GetSound(const std::string& filename);
    
        int mChannel;
    private:
    
        void LoadData();
        void UnloadData();
};


