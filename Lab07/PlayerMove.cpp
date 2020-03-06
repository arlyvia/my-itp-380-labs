//
//  PlayerMove.cpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/5/20.
//

#include "PlayerMove.hpp"
#include "Actor.h"
#include "MoveComponent.h"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_image.h>

PlayerMove::PlayerMove(class Actor* owner)
    :MoveComponent(owner)
{
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    if(keyState[SDL_SCANCODE_W]){
        //mVelocity 
    }
}

void PlayerMove::Update(float deltaTime){
    SetForwardSpeed(x_speed);
    mVelocity = mOwner->GetForward() * GetForwardSpeed();
    mOwner->SetPosition(mOwner->GetPosition() + mVelocity * deltaTime);
}
