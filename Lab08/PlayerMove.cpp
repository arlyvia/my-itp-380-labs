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
#include <iostream>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_image.h>
#include "CollisionComponent.h"

PlayerMove::PlayerMove(class Actor* owner)
    :VehicleMove(owner)
{
    
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
    
    VehicleMove::Update(deltaTime);
    
    Vector3 cameraPos = mOwner->GetPosition() - (mOwner->GetForward() * HDist) +
    (Vector3::UnitZ * VDist);
    
    Vector3 targetPos = mOwner->GetPosition() + (mOwner ->GetForward() * TargetDist);
    
    Matrix4 viewMatrix = Matrix4::CreateLookAt(cameraPos, targetPos, Vector3::UnitZ);
    
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);
    
}
