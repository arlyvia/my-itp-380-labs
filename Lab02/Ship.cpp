//
//  Ship.cpp
//  Lab02
//
//  Created by Arlyvia Chaialee on 1/29/20.
//

#include "Ship.hpp"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Laser.hpp"
#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>

Ship::Ship(class Game* game)
:Actor(game)
{
 // TODO
    this->ship_sc = new SpriteComponent(this);
    this->ship_sc->SetTexture(GetGame()->GetTexture("Assets/Ship.png"));
    this->ship_mc = new MoveComponent(this);
    
}

void Ship::OnUpdate(float deltaTime){
    mElapsedTime = deltaTime + mElapsedTime;
}

void Ship::OnProcessInput(const Uint8* keyState)
{
    
    
    
    if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_DOWN]
        || keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_RIGHT]
        || keyState[SDL_SCANCODE_SPACE]) {
        if (keyState[SDL_SCANCODE_UP]) {
            ship_mc->SetForwardSpeed(300.0f);
            //SpriteComponent* ship_sc = new SpriteComponent(this);
            ship_sc->SetTexture(GetGame()->GetTexture("Assets/ShipThrust.png"));
        }
        if (keyState[SDL_SCANCODE_DOWN]) {
            ship_mc->SetForwardSpeed(-(300.0f));
            ship_sc->SetTexture(GetGame()->GetTexture("Assets/ShipThrust.png"));
        }
        if (keyState[SDL_SCANCODE_LEFT]) {
            ship_mc->SetAngularSpeed(Math::Pi/4);
        }
        if (keyState[SDL_SCANCODE_RIGHT]) {
            ship_mc->SetAngularSpeed(-(Math::Pi/4));
        }
        if(keyState[SDL_SCANCODE_DOWN]&&keyState[SDL_SCANCODE_UP]){
            ship_mc->SetForwardSpeed(0);
            ship_sc->SetTexture(GetGame()->GetTexture("Assets/Ship.png"));
        }
        if(keyState[SDL_SCANCODE_LEFT]&&keyState[SDL_SCANCODE_RIGHT]){
            ship_mc->SetAngularSpeed(0);
        }
        if (keyState[SDL_SCANCODE_SPACE]){
            if(mElapsedTime > 1.0f){
                Laser* laser = new Laser(this->GetGame());
                Vector2 laser_pos = this->mPosition;
                laser->SetPosition(laser_pos);
                laser->SetRotation(this->mRotation);
                mElapsedTime = 0.0f;
            }
            
        }

    } else {
        ship_mc->SetForwardSpeed(0);
        ship_mc->SetAngularSpeed(0);
        ship_sc->SetTexture(GetGame()->GetTexture("Assets/Ship.png"));

    }
}

