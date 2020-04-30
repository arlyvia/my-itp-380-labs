#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
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
    
    class Player* mPlayer = nullptr;
    
    float dist = 3000.0f;

    int mChannel;
    
    std::vector<Actor*> mBlocks;
    
    std::queue <class Checkpoint*> mCheckpoints;
    
    class Arrow* mArrow = nullptr;
    
    std::string mNextLevel = "";
    void SetNextLevel(std::string nextLevel) { mNextLevel = nextLevel; }
    
    void LoadNextLevel();
    
    float mTime = 0.0f;
    int mCoinCount = 0;
    
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
