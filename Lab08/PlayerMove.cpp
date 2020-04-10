//
//  PlayerMove.cpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/5/20.
//

#include "PlayerMove.hpp"
#include "Actor.h"
#include "MoveComponent.h"
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
    mOwner->GetGame()->mPlayer->player_ui->PlayerUI::OnLapChange(newLap);
}
