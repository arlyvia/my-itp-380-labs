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
    class Enemy* mEnemy;
    
    class Player* GetPlayer() const { return mPlayer; }
    class Enemy* GetEnemy() const { return mEnemy; }
    
    float dist = 3000.0f;

    int mChannel;
    
    class HeightMap* mHeightMap;
    
    float mStartTimer = 8.5f;
    bool firstTime = false;
    
    Mix_Chunk * final_lap_sound;
    Mix_Chunk * lost_sound;
    Mix_Chunk * race_start_sound;
    Mix_Chunk * won_sound;
    Mix_Chunk * music;
    Mix_Chunk * music_fast;
    
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
