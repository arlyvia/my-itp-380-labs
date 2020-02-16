//
//  BallMove.cpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 2/5/20.
//

#include "BallMove.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Block.hpp"
#include "Game.h"

#include <iostream>

BallMove::BallMove(class Actor* owner)
    :MoveComponent(owner)
    ,mAngularSpeed(0.0f)
    ,mForwardSpeed(0.0f)
{
    
}

void BallMove::Update(float deltaTime){
    mOwner->SetPosition(mOwner->GetPosition() + ball_velocity * deltaTime);
    
    //ceiling
    if(mOwner->GetPosition().y <= top_wall_limit){
        mOwner->SetPosition(Vector2(mOwner->GetPosition().x, top_wall_offset));
        ball_velocity.y = -ball_velocity.y;
       }
    
    //left wall
    if(mOwner->GetPosition().x <= left_wall_limit) {
        mOwner->SetPosition(Vector2(left_wall_offset, mOwner->GetPosition().y));
        ball_velocity.x = -ball_velocity.x;
    }
    
    //right wall
   if(mOwner->GetPosition().x >= right_wall_limit){
       mOwner->SetPosition(Vector2(right_wall_offset, mOwner->GetPosition().y));
       ball_velocity.x = -ball_velocity.x;
   }

    //bottom
    if(mOwner->GetPosition().y >= bottom_edge + ball_size){
        Vector2 pos_ball = Vector2(mOwner->GetGame()->horizontal_center, mOwner->GetGame()->paddle_pos_y - dist_to_init_pos);
        mOwner->SetPosition(pos_ball);
        ball_velocity = Vector2(250, -250);
    }
    
    //paddle collisions
    if(owner_cc->Intersect(local_paddle->GetComponent<CollisionComponent>()) ){
            if((mOwner->GetPosition().x >= this->local_paddle->GetPosition().x-half_paddle_w)
                    && (mOwner->GetPosition().x <= this->local_paddle->GetPosition().x-half_paddle_h)
               && ball_velocity.y > 0){
                
                Vector2 normal_middle = Vector2(-0.1f, -0.9f);
                normal_middle.Normalize();
                ball_velocity = Vector2::Reflect(ball_velocity,normal_middle);
                
                mOwner->SetPosition(Vector2(mOwner->GetPosition().x-1.0f, mOwner->GetPosition().y-1.0f));
            }
            else if((mOwner->GetPosition().x >= this->local_paddle->GetPosition().x-half_paddle_h)
            && (mOwner->GetPosition().x <= this->local_paddle->GetPosition().x+half_paddle_h)
                    && ball_velocity.y > 0){
                Vector2 normal_left = Vector2(0,-1);
                ball_velocity = Vector2::Reflect(ball_velocity,normal_left);
                
                mOwner->SetPosition(Vector2(mOwner->GetPosition().x, mOwner->GetPosition().y-1.0f));
            }
            else if((mOwner->GetPosition().x >= this->local_paddle->GetPosition().x+half_paddle_h)
            && (mOwner->GetPosition().x <= this->local_paddle->GetPosition().x+half_paddle_w)
                    && ball_velocity.y > 0){
                
                Vector2 normal_right = Vector2(0.1f, -0.9f);
                normal_right.Normalize();
                ball_velocity = Vector2::Reflect(ball_velocity,normal_right);
                
                mOwner->SetPosition(Vector2(mOwner->GetPosition().x+1.0f, mOwner->GetPosition().y-1.0f));
            }
    }
    
    //block collisions
    Vector2 local_offset;
    for(int i=0; i < (signed)(mOwner->GetGame()->mBlocks.size()); i++){
        
        CollSide side = owner_cc->GetMinOverlap(mOwner->GetGame()->mBlocks[i]->GetComponent<CollisionComponent>(), local_offset);
        
        if(side != CollSide::None){
            if(side == CollSide::Top){
                Vector2 normal_top = Vector2(0, -1.0f);
                ball_velocity = Vector2::Reflect(ball_velocity,normal_top);
            } else if(side == CollSide::Bottom){
                Vector2 normal_top = Vector2(0, 1.0f);
                ball_velocity = Vector2::Reflect(ball_velocity,normal_top);
            } else if(side == CollSide::Right){
                Vector2 normal_top = Vector2(-1.0f, 0);
                ball_velocity = Vector2::Reflect(ball_velocity,normal_top);
            } else if(side == CollSide::Left){
                Vector2 normal_top = Vector2(1.0f, 0);
                ball_velocity = Vector2::Reflect(ball_velocity,normal_top);
            }
            
            mOwner->GetGame()->mBlocks[i]->SetState(ActorState::Destroy);
            break;
        }
    }  
}
