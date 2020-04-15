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
#include "Math.h"
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
        AddForce(mOwner->GetForward() * 700.0f);
    } else if(keyState[SDL_SCANCODE_S]){
        AddForce(mOwner->GetForward() * -700.0f);
    } else {
        AddForce(Vector3::Zero);
    }
    
    if(keyState[SDL_SCANCODE_A]){
        AddForce(mOwner->GetRight() * -700.0f);
    } else if(keyState[SDL_SCANCODE_D]){
        AddForce(mOwner->GetRight() * 700.0f);
    } else {
        AddForce(Vector3::Zero);
    }
    
    //mouse rotation
    int x, y;
    SDL_GetRelativeMouseState(&x, &y);
   
    SetAngularSpeed(x / 500.0f * Math::Pi * 10.0f);

    float b = (float)y / 500.0f * Math::Pi * 10.0f;
    mOwner->GetComponent<CameraComponent>()->SetPitchSpeed(b);
    
    if(keyState[SDL_SCANCODE_SPACE]){
        if(!last_frame && keyState[SDL_SCANCODE_SPACE] && mCurrentState == MoveState::OnGround){
            AddForce(mJumpForce);
            ChangeState(MoveState::Jump);
        }
    }
    
    last_frame = keyState[SDL_SCANCODE_SPACE];
}

void PlayerMove::Update(float deltaTime){
    if(mCurrentState == MoveState::OnGround) UpdateOnGround(deltaTime);
    if(mCurrentState == MoveState::Jump) UpdateJump(deltaTime);
    if(mCurrentState == MoveState::Falling) UpdateFalling(deltaTime);
    if(mCurrentState == MoveState::WallClimb) UpdateWallClimb(deltaTime);
}

void PlayerMove::ChangeState(MoveState ms){
    mCurrentState = ms;
}

void PlayerMove::UpdateOnGround(float deltaTime){
    PhysicsUpdate(deltaTime);
    
    standing = false;
    for(int unsigned i = 0; i < mOwner->GetGame()->mBlocks.size(); i++){
        CollSide side = FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>());
        if(side == CollSide::Top) standing = true;
        if(side == CollSide::SideMaxY
           || side == CollSide::SideMinY
           || side == CollSide::SideMaxX
           || side == CollSide::SideMinX){
            //CanWallClimb(side);
            if(CanWallClimb(side)){
                ChangeState(MoveState::WallClimb);
                return;
            } else {
                std::cout << "cannot climb" << std::endl;
            }
        }
    }
    if(!standing){
        standing = false;
        ChangeState(MoveState::Falling);
    }
}

void PlayerMove::UpdateJump(float deltaTime){
    
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    
    for(int unsigned i = 0; i < mOwner->GetGame()->mBlocks.size(); i++){
        CollSide side = FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>());
        if(side == CollSide::Bottom) hit_head = true;
    }
    if(hit_head){
        hit_head = false;
        mVelocity.z = 0.0f;
    } else if(mVelocity.z <= 0.0f){
        //make sure this if statement is in the right place
        ChangeState(MoveState::Falling);
    }
}

void PlayerMove::UpdateFalling(float deltaTime){
    
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    
    for(int unsigned i = 0; i < mOwner->GetGame()->mBlocks.size(); i++){
        CollSide side = FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>());
        if(side == CollSide::Top){
            mVelocity.z = 0;
            ground = true;
        }
    }
    if(ground){
        ground = false;
        ChangeState(MoveState::OnGround);
    }
}

void PlayerMove::UpdateWallClimb(float deltaTime){
    AddForce(mGravity);
    AddForce(mClimbForce);
    PhysicsUpdate(deltaTime);
    collide_side = false;
    for(int unsigned i = 0; i < mOwner->GetGame()->mBlocks.size(); i++){
        CollSide side = FixCollision(mOwner->GetComponent<CollisionComponent>(), mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>());
        if(side == CollSide::SideMaxY
           || side == CollSide::SideMinY
           || side == CollSide::SideMaxX
           || side == CollSide::SideMinX){
            collide_side = true;
        }
    }
    if(!collide_side || mVelocity.z <= 0.0f){
        mVelocity.z = 0.0f;
        ChangeState(MoveState::Falling);
    }
}

CollSide PlayerMove::FixCollision(class CollisionComponent *self, class CollisionComponent* block){
    Vector3 local_offset;
    CollSide side = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(block, local_offset);
    
    if(side != CollSide::None){
        mOwner->SetPosition(mOwner->GetPosition() + local_offset);
    }
    return side;
    
}

void PlayerMove::AddForce(const Vector3 &force){
    mPendingForces += force;
}

void PlayerMove::PhysicsUpdate(float deltaTime){
    mAcceleration = mPendingForces * (1.0f / mMass);
    mVelocity += mAcceleration * deltaTime;
    
    FixXYVelocity();
    
    mOwner->SetPosition(mOwner->GetPosition() + (mVelocity * deltaTime));
    
    mOwner->SetRotation(mOwner->GetRotation() + (GetAngularSpeed() * deltaTime));
    
    mPendingForces = Vector3::Zero;
}

void PlayerMove::FixXYVelocity(){
    Vector2 xyVelocity = Vector2(mVelocity.x, mVelocity.y);
    if(xyVelocity.Length() > 400.0f){
        //normalize function from math would not work here:
        float length = xyVelocity.Length();
        xyVelocity.x /= length;
        xyVelocity.y /= length;
        xyVelocity *= 400.0f;
    }
    
    //braking
    if(mCurrentState == MoveState::OnGround){
        if(Math::NearZero(mAcceleration.x)
           || (mAcceleration.x > 0 && xyVelocity.x < 0)
           || (mAcceleration.x < 0 && xyVelocity.x > 0)){
            xyVelocity.x *= 0.9f;
        }
        if(Math::NearZero(mAcceleration.y)
           || (mAcceleration.y < 0 && xyVelocity.y > 0)
           || (mAcceleration.y > 0 && xyVelocity.y < 0)){
            xyVelocity.y *= 0.9f;
        }
        
    }

    mVelocity.x = xyVelocity.x;
    mVelocity.y = xyVelocity.y;
}

//Wall climbing

bool PlayerMove::CanWallClimb(CollSide side){
    float dot;
    Vector3 normal;
    
    if(side == CollSide::SideMinX){
        normal = Vector3(-1, 0, 0);
    } else if(side == CollSide::SideMaxX){
        normal = Vector3(1, 0, 0);
    } else if(side == CollSide::SideMinY){
        normal = Vector3(0, -1, 0);
    } else {
        normal = Vector3(0, 1, 0);
    }
    
    dot = Vector3::Dot(normal, mOwner->GetForward());
    
    Vector2 xyNormal;
    if(side == CollSide::SideMinX){
        xyNormal = Vector2(-1, 0);
    } else if(side == CollSide::SideMaxX){
        xyNormal = Vector2(1, 0);
    } else if(side == CollSide::SideMinY){
        xyNormal = Vector2(0, -1);
    } else {
        xyNormal = Vector2(0, 1);
    }
    Vector2 xyVelocity = Vector2(mVelocity.x, mVelocity.y);
    
    float xyDot = Vector2::Dot(xyVelocity, xyNormal);
    
    if(dot < -0.9f && xyVelocity.Length() > 350.0f
       && xyDot < 0.9f){
        return true;
    } else {
        return false;
    }
}
