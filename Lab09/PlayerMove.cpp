//
//  PlayerMove.cpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/5/20.
//

#include "PlayerMove.hpp"
#include "Actor.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Renderer.h"
#include <iostream>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_image.h>
#include "CollisionComponent.h"

PlayerMove::PlayerMove(class Actor* owner)
    :MoveComponent(owner)
{
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    if(keyState[SDL_SCANCODE_W]){
        SetForwardSpeed(350.0f);
    } else if(keyState[SDL_SCANCODE_S]){
        SetForwardSpeed(-350.0f);
    } else {
         SetForwardSpeed(0);
    }
    
    /*if(keyState[SDL_SCANCODE_A]){
        mOwner->SetPosition(Vector3(mOwner->GetPosition().x,
                                    mOwner->GetPosition().y - 5.0f,
                                    mOwner->GetPosition().z));
    } else if(keyState[SDL_SCANCODE_D]){
        //yDir = y_speed * speed_multiplier;
    } else {
        //yDir = 0;
    }

    /*if(keyState[SDL_SCANCODE_SPACE]){
        if(!last_frame && keyState[SDL_SCANCODE_SPACE]){
            Bullet* bullet = new Bullet(mOwner->GetGame());
            Vector3 bullet_pos = mOwner->GetPosition();
            bullet->SetPosition(bullet_pos);
            Mix_Chunk* pew = mOwner->GetGame()->GetSound("Assets/Sounds/Shoot.wav");
            Mix_PlayChannel(-1, pew, 0);
        }
    }*/
    
    //last_frame = keyState[SDL_SCANCODE_SPACE];
}

void PlayerMove::Update(float deltaTime){
    MoveComponent::Update(deltaTime);
}
