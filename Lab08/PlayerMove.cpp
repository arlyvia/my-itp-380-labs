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
#include <iostream>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_image.h>
#include "CollisionComponent.h"

PlayerMove::PlayerMove(class Actor* owner)
    :VehicleMove(owner)
{
    mOwner->SetPosition(mOwner->GetGame()->mHeightMap->CellToWorld(39, 58));
    /*std::cout << "celltoworld" << mOwner->GetGame()->mHeightMap->CellToWorld(39, 58).x <<std::endl;
    std::cout << "celltoworld" << mOwner->GetGame()->mHeightMap->CellToWorld(39, 58).y <<std::endl;
    std::cout << "celltoworld" << mOwner->GetGame()->mHeightMap->CellToWorld(39, 58).z <<std::endl;*/
    std::cout << "z" << mOwner->GetPosition().z << std::endl;
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
    /*SetForwardSpeed(x_speed);
    mVelocity = mOwner->GetForward() * GetForwardSpeed();
    mPos = mOwner->GetPosition() + mVelocity * deltaTime;
    mOwner->SetPosition(mPos);
    
    if(mPos.y + yDir * deltaTime < 195.0f && mPos.y + yDir * deltaTime > -195.0f){
        mPos.y += yDir * deltaTime;
    }
    if(mPos.z + zDir * deltaTime < 225.0f && mPos.z + zDir * deltaTime > -225.0f){
        mPos.z += zDir * deltaTime;
    }
    mOwner->SetPosition(mPos);*/
    std::cout << "x" << mOwner->GetPosition().x << std::endl;
    std::cout << "y" << mOwner->GetPosition().y << std::endl;
    std::cout << "z" << mOwner->GetPosition().z << std::endl;
    
    VehicleMove::Update(deltaTime);
    
}
