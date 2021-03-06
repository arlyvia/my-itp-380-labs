#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	Mix_Chunk* GetSound(const std::string& fileName);

	class Renderer* GetRenderer() {	return mRenderer; }
    
    class Player* mPlayer;
    
    class SideBlock* sb1;
    class SideBlock* sb2;
    
    float dist = 3000.0f;
    
    int num_blocks = 6;
    
    std::vector<class Block*> mBlocks;

    void AddBlock(Block* block);
    void RemoveBlock(Block* block);
    
    void loadBlocks(std::string filename);
    
    float block_dist = 1000.0f;
    
    int num_other_blocks = 2;
    
    int mChannel;
    
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	std::unordered_map<std::string, Mix_Chunk*> mSounds;

	// All the actors in the game
	std::vector<class Actor*> mActors;

	class Renderer* mRenderer = nullptr;

	Uint32 mTicksCount = 0;
	bool mIsRunning;
};
