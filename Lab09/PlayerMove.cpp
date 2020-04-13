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
#include "CameraComponent.hpp"
#include <iostream>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_image.h>
#include "CollisionComponent.h"

PlayerMove::PlayerMove(class Actor* owner)
    :MoveComponent(owner)
{
    ChangeState(MoveState::Falling);
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    if(keyState[SDL_SCANCODE_W]){
        SetForwardSpeed(350.0f);
    } else if(keyState[SDL_SCANCODE_S]){
        SetForwardSpeed(-350.0f);
    } else {
         SetForwardSpeed(0);
    }
    
    if(keyState[SDL_SCANCODE_A]){
        SetStrafeSpeed(-350.0f);
    } else if(keyState[SDL_SCANCODE_D]){
        SetStrafeSpeed(350.0f);
    } else {
        SetStrafeSpeed(0);
    }
    
    //mouse rotation
    int x, y;
    SDL_GetRelativeMouseState(&x, &y);
    
    /*float a = (float)x;
    a = float(x / 500.0f);
   
    a = float(x * Math::Pi * 10.0f);*/
   
    SetAngularSpeed(x);

    float b = (float)y;
    mOwner->GetComponent<CameraComponent>()->SetPitchSpeed(y);
    
    if(keyState[SDL_SCANCODE_SPACE]){
        if(!last_frame && keyState[SDL_SCANCODE_SPACE] && mCurrentState == MoveState::OnGround){
            mZSpeed = JumpSpeed;
            ChangeState(MoveState::Jump);
        }
    }
    
    last_frame = keyState[SDL_SCANCODE_SPACE];
}

void PlayerMove::Update(float deltaTime){
    if(mCurrentState == MoveState::OnGround) UpdateOnGround(deltaTime);
    if(mCurrentState == MoveState::Jump) UpdateJump(deltaTime);
    if(mCurrentState == MoveState::Falling) UpdateFalling(deltaTime);
}

void PlayerMove::ChangeState(MoveState ms){
    mCurrentState = ms;
}

void PlayerMove::UpdateOnGround(float deltaTime){
    MoveComponent::Update(deltaTime);
    for(int unsigned i = 0; i < mOwner->GetGame()->mBlocks.size(); i++){
        CollSide side = FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>());
        if(side == CollSide::Top) standing = true;
    }
    if(standing){
        standing = false;
        ChangeState(MoveState::Falling);
    }
}

void PlayerMove::UpdateJump(float deltaTime){
    MoveComponent::Update(deltaTime);
    mZSpeed = mZSpeed + (Gravity * deltaTime);
    mOwner->SetPosition(Vector3(mOwner->GetPosition().x,
                        mOwner->GetPosition().y,
                        mOwner->GetPosition().z + (mZSpeed * deltaTime)));
    for(int unsigned i = 0; i < mOwner->GetGame()->mBlocks.size(); i++){
        CollSide side = FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>());
        if(side == CollSide::Bottom) hit_head = true;
    }
    if(hit_head){
        hit_head = false;
        mZSpeed = 0.0f;
    } else if(mZSpeed <= 0.0f){
        //make sure this if statement is in the right place
        ChangeState(MoveState::Falling);
    }
}

void PlayerMove::UpdateFalling(float deltaTime){
    MoveComponent::Update(deltaTime);
    mZSpeed = mZSpeed + (Gravity * deltaTime);
    mOwner->SetPosition(Vector3(mOwner->GetPosition().x,
                        mOwner->GetPosition().y,
                        mOwner->GetPosition().z + (mZSpeed * deltaTime)));
    for(int unsigned i = 0; i < mOwner->GetGame()->mBlocks.size(); i++){
        CollSide side = FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>());
        if(side == CollSide::Top){
            mZSpeed = 0;
            ground = true;
        }
    }
    if(ground){
        ground = false;
        ChangeState(MoveState::OnGround);
    }
}

CollSide PlayerMove::FixCollision(class CollisionComponent *self, class CollisionComponent* block){
    Vector3 local_offset;
    CollSide side = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(block, local_offset);
    if(side != CollSide::None){
        if(side == CollSide::Top){
            mOwner->SetPosition(mOwner->GetPosition()+local_offset);
        } else if(side == CollSide::Bottom){
            mOwner->SetPosition(mOwner->GetPosition()-local_offset);
        }
    }
    return side;
    
}
