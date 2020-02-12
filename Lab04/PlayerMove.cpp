//
//  PlayerMove.cpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#include "PlayerMove.hpp"
#include "MoveComponent.h"
#include "Math.h"
#include "CollisionComponent.h"
#include "Block.hpp"
#include <SDL2/SDL_image.h>

PlayerMove::PlayerMove(class Actor* owner)
    :MoveComponent(owner)
{
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState) {
    if (keyState[SDL_SCANCODE_LEFT]) {
        this->SetForwardSpeed(-300.0f);
    } else if (keyState[SDL_SCANCODE_RIGHT]){
        this->SetForwardSpeed(300.0f);
    } else {
         this->SetForwardSpeed(0);
    }
}

void PlayerMove::Update(float deltaTime){
    Vector2 velocity = mOwner->GetForward() * GetForwardSpeed();
    mOwner->SetPosition(mOwner->GetPosition() + velocity * deltaTime);
    
    mYSpeed = mYSpeed + 2000.0f * deltaTime;
    
    Vector2 local_offset(0, 0);
    for(int i=0; i < (signed)mOwner->GetGame()->mBlocks.size(); i++){
        CollSide side = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>(), local_offset);
        
        if(side != CollSide::None){
            if(side == CollSide::Top && mYSpeed > 0.0f){
                mYSpeed = 0;
            }
        }
    }
    
    if(mOwner->GetPosition().y < 448.0f){
        Vector2 velocity_y(0, mYSpeed);
        mOwner->SetPosition(mOwner->GetPosition() + velocity_y * deltaTime);
    }
}
