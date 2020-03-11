//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include <algorithm>
#include "Actor.h"
#include <fstream>
#include "Renderer.h"
#include "Random.h"
#include "Player.hpp"
#include "SideBlock.hpp"
#include "MeshComponent.h"
#include <iostream>

Game::Game()
:mIsRunning(true)
{
	
}

bool Game::Initialize()
{
	Random::Init();

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// TODO: Create renderer
    mRenderer = new Renderer(this);
    if(!mRenderer->Initialize(1024.0f, 768.0f)) return false;;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	LoadData();

	mTicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.01667f)
	{
		deltaTime = 0.01667f;
	}
	mTicksCount = SDL_GetTicks();
	
	// Make copy of actor vector
	// (iterate over this in case new actors are created)
	std::vector<Actor*> copy = mActors;
	// Update all actors
	for (auto actor : copy)
	{
		actor->Update(deltaTime);
	}

	// Add any actors to destroy to a temp vector
	std::vector<Actor*> destroyActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == ActorState::Destroy)
		{
			destroyActors.emplace_back(actor);
		}
	}

	// Delete the destroyed actors (which will
	// remove them from mActors)
	for (auto actor : destroyActors)
	{
		delete actor;
	}
    
    //spawning sideblocks
    if(dist - mPlayer->GetPosition().x < 3000.0f){
        num_blocks++;
    
        SideBlock* sb_right = new SideBlock(this);
        sb_right->SetPosition(Vector3(dist, 500, 0));
        sb_right->SetScale(sb_right->mScale);
        if(num_blocks%2 == 0) {
            sb_right->GetComponent<MeshComponent>()->SetTextureIndex(4);
        } else {
            sb_right->GetComponent<MeshComponent>()->SetTextureIndex(3);
        }
        
        SideBlock* sb_left = new SideBlock(this);
        sb_left->SetPosition(Vector3(dist, -500, 0));
        sb_left->SetScale(sb_left->mScale);
        if(num_blocks%2 == 0) {
            sb_left->GetComponent<MeshComponent>()->SetTextureIndex(4);
        } else {
            sb_left->GetComponent<MeshComponent>()->SetTextureIndex(3);
        }
        
        dist = dist + 500.0f;
    }
}

void Game::GenerateOutput()
{
	// TODO: tell renderer to draw
    mRenderer->Draw();
}

void Game::LoadData()
{
    mPlayer = new Player(this);
    
    Matrix4 projMatrix = Matrix4::CreatePerspectiveFOV(1.22f, 1024.0f, 768.0f, 10.0f, 10000.0f);
    mRenderer->SetProjectionMatrix(projMatrix);
    
    Vector3 eye_pos = Vector3(-300, 0, 100);
    Vector3 tar_pos = Vector3(20, 0, 0);
    Matrix4 viewMatrix = Matrix4::CreateLookAt(eye_pos, tar_pos, Vector3::UnitZ);
    mRenderer->SetViewMatrix(viewMatrix);
    
    //original sideblocks
    for(int i = 0; i < 6; i++){
        SideBlock* sb = new SideBlock(this);
        sb->SetPosition(Vector3(i*500, 500, 0));
        std::cout << 500*i << std::endl;
        sb->SetScale(sb->mScale);
        if(i%2 == 0) {
            sb->GetComponent<MeshComponent>()->SetTextureIndex(3);
        } else {
            sb->GetComponent<MeshComponent>()->SetTextureIndex(4);
        }
    }
    for(int i = 0; i < 6; i++){
        SideBlock* sb = new SideBlock(this);
        sb->SetPosition(Vector3(i*500, -500, 0));
        sb->SetScale(sb->mScale);
        if(i%2 == 0) {
            sb->GetComponent<MeshComponent>()->SetTextureIndex(3);
        } else {
            sb->GetComponent<MeshComponent>()->SetTextureIndex(4);
        }
    }
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy sounds
	for (auto s : mSounds)
	{
		Mix_FreeChunk(s.second);
	}
	mSounds.clear();
}

Mix_Chunk* Game::GetSound(const std::string& fileName)
{
	Mix_Chunk* chunk = nullptr;
	auto iter = mSounds.find(fileName);
	if (iter != mSounds.end())
	{
		chunk = iter->second;
	}
	else
	{
		chunk = Mix_LoadWAV(fileName.c_str());
		if (!chunk)
		{
			SDL_Log("Failed to load sound file %s", fileName.c_str());
			return nullptr;
		}

		mSounds.emplace(fileName, chunk);
	}
	return chunk;
}

void Game::Shutdown()
{
	UnloadData();
	Mix_CloseAudio();
	// TODO: Delete renderer
    mRenderer->Shutdown();
    delete mRenderer;
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		auto iter2 = mActors.end() - 1;
		std::iter_swap(iter, iter2);
		mActors.pop_back();
	}
}
