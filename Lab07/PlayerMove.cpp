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
#include "SideBlock.hpp"
#include "Renderer.h"
#include "Bullet.hpp"
#include <iostream>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_image.h>

PlayerMove::PlayerMove(class Actor* owner)
    :MoveComponent(owner)
{
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    if(keyState[SDL_SCANCODE_W]){
        zDir = z_speed;
    } else if(keyState[SDL_SCANCODE_S]){
        zDir = -z_speed;
    } else {
        zDir = 0;
    }
    
    if(keyState[SDL_SCANCODE_A]){
        yDir = -y_speed;
    } else if(keyState[SDL_SCANCODE_D]){
        yDir = y_speed;
    } else {
        yDir = 0;
    }
    
    if (keyState[SDL_SCANCODE_SPACE]){
        if(mElapsedTime > 1.0f){
            Bullet* bullet = new Bullet(mOwner->GetGame());
            Vector3 bullet_pos = mOwner->GetPosition();
            bullet->SetPosition(bullet_pos);
            mElapsedTime = 0.0f;
        }
        
    }
}

void PlayerMove::Update(float deltaTime){
    mElapsedTime = deltaTime + mElapsedTime;
    
    SetForwardSpeed(x_speed);
    mVelocity = mOwner->GetForward() * GetForwardSpeed();
    mPos = mOwner->GetPosition() + mVelocity * deltaTime;
    mOwner->SetPosition(mPos);
    
    if(mPos.y + yDir * deltaTime < 195.0f && mPos.y + yDir * deltaTime > -195.0f){
        mPos.y += yDir * deltaTime;
    }
    if(mPos.z + zDir * deltaTime < 225.0f && mPos.z + zDir * deltaTime > -225.0f){
        mPos.z += zDir * deltaTime;
    }
    mOwner->SetPosition(mPos);
    
    Vector3 cameraPos = mOwner->GetPosition() - (mOwner->GetForward() * HDist) +
    (Vector3::UnitZ * VDist);
    
    Vector3 targetPos = mOwner->GetPosition() + (mOwner ->GetForward() * TargetDist);
    
    Matrix4 viewMatrix = Matrix4::CreateLookAt(cameraPos, targetPos, Vector3::UnitZ);
    
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);
    
}
