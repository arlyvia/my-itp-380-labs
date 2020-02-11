//
//  BallMove.cpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 2/5/20.
//

#include "BallMove.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "CollisionComponent.h"
#include "Math.h"

BallMove::BallMove(class Actor* owner)
    :MoveComponent(owner)
    ,mAngularSpeed(0.0f)
    ,mForwardSpeed(0.0f)
{
    
}

void BallMove::Update(float deltaTime){
    mOwner->SetPosition(mOwner->GetPosition() + ball_velocity * deltaTime);
    
    //top
    if(mOwner->GetPosition().y <= top_wall_limit){
        mOwner->SetPosition(Vector2(mOwner->GetPosition().x, top_wall_offset));
        ball_velocity.y = -ball_velocity.y;
       }
    
    //left
    if(mOwner->GetPosition().x <= left_wall_limit) {
        mOwner->SetPosition(Vector2(left_wall_offset, mOwner->GetPosition().y));
        ball_velocity.x = -ball_velocity.x;
    }
    
    //right
   if(mOwner->GetPosition().x >= right_wall_limit){
       mOwner->SetPosition(Vector2(right_wall_offset, mOwner->GetPosition().y));
       ball_velocity.x = -ball_velocity.x;
   }

    //becomes bottom
    if(mOwner->GetPosition().y >= bottom_edge + 20){
       //&& (paddle.x <= mOwner->GetPosition().x) && (mOwner->GetPosition().y < paddle.y+100)){
        Vector2 pos_ball = Vector2(mOwner->GetGame()->horizontal_center, mOwner->GetGame()->paddle_pos_y - 100);
        mOwner->SetPosition(pos_ball);
        ball_velocity = Vector2(250, -250);
    }
    
    if(mOwner->GetComponent<CollisionComponent>()->Intersect(mOwner->GetGame()->GetPaddle()->GetComponent<CollisionComponent>())){
            if((mOwner->GetPosition().x >= this->mOwner->GetGame()->GetPaddle()->GetPosition().x-52.0f)
                    && (mOwner->GetPosition().x <= this->mOwner->GetGame()->GetPaddle()->GetPosition().x-18.0f)){
                
                Vector2 normal_middle = Vector2(-0.5f, -0.866f);
                ball_velocity = Vector2::Reflect(ball_velocity,normal_middle);
                
                mOwner->SetPosition(Vector2(mOwner->GetPosition().x-1.0f, mOwner->GetPosition().y-1.0f));
            }
            else if((mOwner->GetPosition().x >= this->mOwner->GetGame()->GetPaddle()->GetPosition().x-18.0f)
            && (mOwner->GetPosition().x <= this->mOwner->GetGame()->GetPaddle()->GetPosition().x+18.0f)){
                Vector2 normal_middle = Vector2(0,-1);
                ball_velocity = Vector2::Reflect(ball_velocity,normal_middle);
                
                mOwner->SetPosition(Vector2(mOwner->GetPosition().x, mOwner->GetPosition().y-1.0f));
            }
            else if((mOwner->GetPosition().x >= this->mOwner->GetGame()->GetPaddle()->GetPosition().x+18.0f)
            && (mOwner->GetPosition().x <= this->mOwner->GetGame()->GetPaddle()->GetPosition().x+52.0f)){
                
                Vector2 normal_middle = Vector2(0.5f, -0.866f);
                ball_velocity = Vector2::Reflect(ball_velocity,normal_middle);
                
                mOwner->SetPosition(Vector2(mOwner->GetPosition().x+1.0f, mOwner->GetPosition().y-1.0f));
            }
    }
    
}
