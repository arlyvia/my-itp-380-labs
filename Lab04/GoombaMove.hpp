//
//  GoombaMove.hpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#ifndef GoombaMove_hpp
#define GoombaMove_hpp

#include <stdio.h>
#include "MoveComponent.h"
#include "Component.h"
#include "Actor.h"
#include "Game.h"
#include "GoombaMove.hpp"
#include "SDL2/SDL.h"

class GoombaMove: public MoveComponent {
    public:
        //constructor
        GoombaMove(class Actor* owner);
        void Update(float deltaTime) override;
    
        float goombaYSpeed = 0;
    
        bool stomped = false;
        //no magic numbers
        float bottom_of_screen = 448.0f;
        
        float goomba_walk_speed = 100.0f;
};

#endif /* GoombaMove_hpp */
