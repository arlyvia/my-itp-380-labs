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
#include "AnimatedSprite.h"
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
    
        void Player_Animate(std::string mAnimName, std::vector<SDL_Texture *> Anims);
        
        //no magic numbers
        float bottom_of_screen = 448.0f;
        float jump_speed = 350.0f;
        float player_walk_speed = 300.0f;
        float pole_x_pos = 6368.0f;
};

#endif /* PlayerMove_hpp */
