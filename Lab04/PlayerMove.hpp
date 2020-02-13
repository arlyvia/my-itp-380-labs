//
//  PlayerMove.hpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#ifndef PlayerMove_hpp
#define PlayerMove_hpp

#include <stdio.h>
#include "MoveComponent.h"
#include "Component.h"
#include "Actor.h"
#include "Game.h"
#include "SDL2/SDL.h"

class PlayerMove: public MoveComponent {
    public:
        //constructor
        PlayerMove(class Actor* owner);
    
        void ProcessInput(const Uint8* keyState) override;
        void Update(float deltaTime) override;
    
        float mYSpeed = 0;
    
        bool mSpacePressed = false;
        bool mInAir = false;
        bool last_frame = false;
};

#endif /* PlayerMove_hpp */
