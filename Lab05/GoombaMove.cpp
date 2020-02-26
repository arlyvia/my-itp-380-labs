//
//  GoombaMove.cpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#include "GoombaMove.hpp"
#include "MoveComponent.h"
#include "Goomba.hpp"
#include "Math.h"
#include "CollisionComponent.h"
#include "Block.hpp"
#include <SDL2/SDL_image.h>

GoombaMove::GoombaMove(class Actor* owner)
    :MoveComponent(owner)
{
    this->SetForwardSpeed(-goomba_walk_speed);
}

void GoombaMove::Update(float deltaTime){
    if(!stomped){
        Vector2 velocity = mOwner->GetForward() * GetForwardSpeed();
        mOwner->SetPosition(mOwner->GetPosition() + velocity * deltaTime);
        
        goombaYSpeed = goombaYSpeed + 1500.0f * deltaTime;

        Vector2 local_offset(0, 0);
        for(int i=0; i < (signed)mOwner->GetGame()->mBlocks.size(); i++){
            CollSide side = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>(), local_offset);
            
            if(side != CollSide::None){
                if(side == CollSide::Top && goombaYSpeed > 0.0f){
                    mOwner->SetPosition(mOwner->GetPosition()+local_offset);
                    goombaYSpeed = 0;
                } else if(side == CollSide::Bottom && goombaYSpeed < 0.0f){
                    mOwner->SetPosition(mOwner->GetPosition()-local_offset);
                    goombaYSpeed = 0;
                }else if(side == CollSide::Left){
                    this->SetForwardSpeed(-goomba_walk_speed);
                } else if(side == CollSide::Right){
                    this->SetForwardSpeed(goomba_walk_speed);
                }
            }
        }
        
        for(int i=0; i < (signed)mOwner->GetGame()->mEnemies.size(); i++){
            CollSide side = mOwner->GetComponent<CollisionComponent>()->GetMinOverlap(mOwner->GetGame()->mEnemies[i]->GetComponent<CollisionComponent>(), local_offset);
            
            if(side != CollSide::None){
                if(side == CollSide::Left){
                    this->SetForwardSpeed(-goomba_walk_speed);
                } else if(side == CollSide::Right){
                    this->SetForwardSpeed(goomba_walk_speed);
                }
            }
        }
        
        if(mOwner->GetPosition().y < bottom_of_screen){
            Vector2 velocity_y(0, goombaYSpeed);
            mOwner->SetPosition(mOwner->GetPosition() + velocity_y * deltaTime);
        }else{
            auto it = std::find(mOwner->GetGame()->mEnemies.begin(), mOwner->GetGame()->mEnemies.end(),mOwner);
            if(it != mOwner->GetGame()->mEnemies.end())
            {
                mOwner->GetGame()->mEnemies.erase(it);
            }

            mOwner->SetState(ActorState::Destroy);
            
        }
    }
    
    
}
