//
//  PlayerMove.cpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#include "PlayerMove.hpp"
#include "MoveComponent.h"
#include "Goomba.hpp"
#include "Math.h"
#include "CollisionComponent.h"
#include "Block.hpp"
#include <SDL2/SDL_image.h>

PlayerMove::PlayerMove(class Actor* owner)
    :MoveComponent(owner)
{
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState) {
   // mSpacePressed = false;
    if (keyState[SDL_SCANCODE_LEFT]) {
        this->SetForwardSpeed(-300.0f);
    } else if (keyState[SDL_SCANCODE_RIGHT]){
        this->SetForwardSpeed(300.0f);
    } else {
         this->SetForwardSpeed(0);
    }
    
    if(keyState[SDL_SCANCODE_SPACE]){
        if(!last_frame && keyState[SDL_SCANCODE_SPACE] && !mInAir){
            mYSpeed = -700.0f;
            mInAir = true;
        }
    }
    
    last_frame = keyState[SDL_SCANCODE_SPACE];
}

void PlayerMove::Update(float deltaTime){
    Vector2 velocity = mOwner->GetForward() * GetForwardSpeed();
    mOwner->SetPosition(mOwner->GetPosition() + velocity * deltaTime);
    
    mYSpeed = mYSpeed + 1500.0f * deltaTime;
    
    bool local_coll;
    
    Vector2 local_offset(0, 0);
    for(int i=0; i < (signed)mOwner->GetGame()->mBlocks.size(); i++){
        CollSide side = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>(), local_offset);
        
        if(side != CollSide::None){
            local_coll = true;
            if(side == CollSide::Top && mYSpeed > 0.0f){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
                mYSpeed = 0;
                mInAir = false;
            } else if(side == CollSide::Bottom && mYSpeed < 0.0f){
                mOwner->SetPosition(mOwner->GetPosition()-local_offset);
                mYSpeed = 0;
                mInAir = false;
            }else if(side == CollSide::Left){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
            } else if(side == CollSide::Right){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
            }
        }
    }
    
    for(int i=0; i < (signed)mOwner->GetGame()->mEnemies.size(); i++){
        CollSide side = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->mEnemies[i]->GetComponent<CollisionComponent>(), local_offset);
        
        if(side != CollSide::None){
            local_coll = true;
            if(side == CollSide::Top && mYSpeed > 0.0f){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
                mYSpeed = -350.0f;
                mInAir = true;
                
                mOwner->GetGame()->mEnemies[i]->stomp();
                
            } else if(side == CollSide::Left && mInAir){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
                mYSpeed = -350.0f;
                mOwner->GetGame()->mEnemies[i]->stomp();
                
            } else if(side == CollSide::Right && mInAir){
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
                mYSpeed = -350.0f;
                mOwner->GetGame()->mEnemies[i]->stomp();
                
            }else {
                mOwner->SetPosition(mOwner->GetPosition()+local_offset);
                mOwner->GetComponent<SpriteComponent>()->SetTexture(mOwner->GetGame()->GetTexture("Assets/Mario/Dead.png"));
                mOwner->SetState(ActorState::Paused);
            }
        }
    }

    
    if(local_coll){
        //mInAir = true;
    }
    
    if(mOwner->GetPosition().y < 448.0f){
        Vector2 velocity_y(0, mYSpeed);
        mOwner->SetPosition(mOwner->GetPosition() + velocity_y * deltaTime);
    }
    
    float temp_camera_pos = mOwner->GetGame()->camera_pos.x;
    
    if(GetForwardSpeed() <= 0.0f){
        if(mOwner->GetGame()->camera_pos.x > mOwner->GetPosition().x){
            mOwner->SetPosition(Vector2(mOwner->GetGame()->camera_pos.x,
                                        mOwner->GetPosition().y));
        }
    } else {
        if(mOwner->GetPosition().x - temp_camera_pos < 300.0f){
            mOwner->GetGame()->camera_pos.x = temp_camera_pos;
        } else {
            mOwner->GetGame()->camera_pos.x = mOwner->GetPosition().x - 300.0f;
        }
    }
}
