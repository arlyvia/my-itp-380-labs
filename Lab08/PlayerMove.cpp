//
//  PlayerMove.cpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/5/20.
//

#include "PlayerMove.hpp"
#include "Actor.h"
#include "MoveComponent.h"
#include "VehicleMove.hpp"
#include "Enemy.hpp"
#include "Game.h"
#include "Renderer.h"
#include "HeightMap.hpp"
#include "Player.hpp"
#include "PlayerUI.h"
#include <iostream>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_image.h>
#include "CollisionComponent.h"

PlayerMove::PlayerMove(class Actor* owner)
    :VehicleMove(owner)
{
    mOwner->SetPosition(mOwner->GetGame()->mHeightMap->CellToWorld(39, 58));
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    if(keyState[SDL_SCANCODE_W]){
        SetPressed(true);
    } else {
        SetPressed(false);
    }
    
    if(keyState[SDL_SCANCODE_A]){
        SetTurn(Turn::Left);
    } else if(keyState[SDL_SCANCODE_D]){
        SetTurn(Turn::Right);
    } else {
    SetTurn(Turn::None);
    }
}

void PlayerMove::Update(float deltaTime){
    
    VehicleMove::Update(deltaTime);
    
}

void PlayerMove::OnLapChange(int newLap){
    if(newLap == 4){
        Mix_FadeOutChannel(mOwner->GetGame()->mChannel, 250);
        
        if(Mix_PlayChannel(-1, mOwner->GetGame()->final_lap_sound, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
        
        Mix_FadeInChannel(mOwner->GetGame()->mChannel, mOwner->GetGame()->music, -1, 400);
    }
    if(newLap >= 5){
        Mix_FadeOutChannel(mOwner->GetGame()->mChannel, 250);
        //std::cout << "2" << std::endl;
        if(mOwner->GetGame()->GetPlayer()->GetComponent<VehicleMove>()->GetCurrentLap() > mOwner->GetGame()->GetEnemy()->GetComponent<VehicleMove>()->GetCurrentLap()){
            if(Mix_PlayChannel(-1, mOwner->GetGame()->won_sound, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
            mOwner->GetComponent<PlayerUI>()->SetRaceState(PlayerUI::Won);
        } else {
            if(Mix_PlayChannel(-1, mOwner->GetGame()->lost_sound, 0)==-1) {
                printf("Mix_PlayChannel: %s\n",Mix_GetError());
            }
            mOwner->GetComponent<PlayerUI>()->SetRaceState(PlayerUI::Lost);
        }
        mOwner->GetGame()->GetEnemy()->SetState(ActorState::Paused);
        mOwner->GetGame()->GetPlayer()->SetState(ActorState::Paused);
    }
    mOwner->GetGame()->mPlayer->player_ui->PlayerUI::OnLapChange(newLap);
}
