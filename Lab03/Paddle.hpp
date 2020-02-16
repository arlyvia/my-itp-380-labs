//
//  Paddle.hpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 1/30/20.
//

#pragma once
#include <stdio.h>
#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"


class Paddle: public Actor {
    public:
        Paddle(class Game* game);
            
        
        //member variables
        int mDirection = 0;
        SpriteComponent* paddle_sc;
        MoveComponent* paddle_mc;
        CollisionComponent* paddle_cc;
    
        int paddle_speed = 500;
        
        void OnProcessInput(const Uint8* keyState) override;
};
