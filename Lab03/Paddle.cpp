//
//  Paddle.cpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 1/30/20.
//

#include "Paddle.hpp"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>

Paddle::Paddle(class Game* game)
:Actor(game)
{
   this->paddle_sc = new SpriteComponent(this);
  this->paddle_sc->SetTexture(GetGame()->GetTexture("Assets/Paddle.png"));
  this->paddle_mc = new MoveComponent(this);
}

void Paddle::OnProcessInput(const Uint8* keyState)
{
    if (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_RIGHT]) {
        if (keyState[SDL_SCANCODE_LEFT]) {
            paddle_mc->SetForwardSpeed(-paddle_speed);
        }
        if (keyState[SDL_SCANCODE_RIGHT]) {
            paddle_mc->SetForwardSpeed(paddle_speed);
        }

    } else {
        paddle_mc->SetForwardSpeed(0);
        paddle_mc->SetAngularSpeed(0);

    }
}


