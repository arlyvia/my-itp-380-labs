//
//  BallMove.hpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 2/5/20.
//

#pragma once
#include <stdio.h>
#include "MoveComponent.h"
#include "Math.h"
#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include "CollisionComponent.h"

class BallMove: public MoveComponent {
    public:
        //constructor
        BallMove(class Actor* owner);
        
       
        Vector2 ball_velocity = Vector2(250, -250);
    
        //methods
        void Update(float deltaTime) override;
   
        //member variables
        float mAngularSpeed;
        float mForwardSpeed;
        float top_wall_limit = 42.0f;
        float top_wall_offset = 43.0f;
        float left_wall_limit = 42.0f;
        float left_wall_offset = 43.0f;
        float right_wall_limit = 982.0f;
        float right_wall_offset = 981.0f;
        float bottom_edge = 768.0f;
    
        const float ball_size = 20.0f;
    
        const float dist_to_init_pos = 100.0f;
    
        const float half_paddle_w = 52.0f;
        const float half_paddle_h = 18.0f;
    
        Paddle* local_paddle = mOwner->GetGame()->GetPaddle();
        CollisionComponent* owner_cc = mOwner->GetComponent<CollisionComponent>();
};

