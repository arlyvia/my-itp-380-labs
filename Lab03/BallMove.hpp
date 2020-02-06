//
//  BallMove.hpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 2/5/20.
//

#ifndef BallMove_hpp
#define BallMove_hpp

#include <stdio.h>
#include "MoveComponent.h"
#include "Math.h"
#include "Actor.h"
#include "Game.h"
#include "Component.h"

#endif /* BallMove_hpp */

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
        float top_wall_limit = 32.0f;
        float top_wall_offset = 33.0f;
        float left_wall_limit = 32.0f;
        float left_wall_offset = 33.0f;
        float right_wall_limit = 992.0f;
        float right_wall_offset = 991.0f;
        float bottom_edge = 768.0f;
};

