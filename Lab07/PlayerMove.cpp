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
#include "CollisionComponent.h"
#include "Block.hpp"

PlayerMove::PlayerMove(class Actor* owner)
    :MoveComponent(owner)
{
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    if(keyState[SDL_SCANCODE_W]){
        zDir = z_speed * speed_multiplier;
    } else if(keyState[SDL_SCANCODE_S]){
        zDir = -z_speed * speed_multiplier;
    } else {
        zDir = 0;
    }
    
    if(keyState[SDL_SCANCODE_A]){
        yDir = -y_speed * speed_multiplier;
    } else if(keyState[SDL_SCANCODE_D]){
        yDir = y_speed * speed_multiplier;
    } else {
        yDir = 0;
    }
    
    if (keyState[SDL_SCANCODE_SPACE]){
        if(mElapsedTime > 1.0f){
            Bullet* bullet = new Bullet(mOwner->GetGame());
            Vector3 bullet_pos = mOwner->GetPosition();
            bullet->SetPosition(bullet_pos);
            mElapsedTime = 0.0f;
            Mix_Chunk* pew = mOwner->GetGame()->GetSound("Assets/Sounds/Shoot.wav");
            Mix_PlayChannel(-1, pew, 0);
        }
        
    }
}

void PlayerMove::Update(float deltaTime){
    mElapsedTime = deltaTime + mElapsedTime;
    mSpeedTimer = deltaTime + mSpeedTimer;
    
    if(mSpeedTimer > 10.0f){
        mSpeedTimer = 0;
        speed_multiplier = speed_multiplier + 0.15f;
    }
    
    SetForwardSpeed(x_speed * speed_multiplier);
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
    
    for(int i=0; i < (signed)(int)mOwner->GetGame()->mBlocks.size(); i++){
        if(mOwner->GetComponent<CollisionComponent>()->Intersect(mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>())){
            mOwner->SetState(ActorState::Paused);
            Mix_Chunk* die_sound = mOwner->GetGame()->GetSound("Assets/Sounds/ShipDie.wav");
            Mix_HaltChannel(mOwner->GetGame()->mChannel);
            Mix_PlayChannel(-1, die_sound, 0);
        }
    }
}
