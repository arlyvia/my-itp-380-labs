//
//  Laser.cpp
//  Lab02
//
//  Created by Arlyvia Chaialee on 2/3/20.
//

#include "Laser.hpp"
#include "Actor.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Asteroid.hpp"
#include "Math.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL_image.h>

Laser::Laser(class Game* game)
:Actor(game)
{
 // TODO
    this->laser_sc = new SpriteComponent(this);
    this->laser_sc->SetTexture(GetGame()->GetTexture("Assets/Laser.png"));
    this->laser_mc = new MoveComponent(this);
    this->laser_mc->SetForwardSpeed(400.0f);
}

void Laser::OnUpdate(float deltaTime){
    lifetime = deltaTime + lifetime;
    if(lifetime > 1.0f){
        this->SetState(ActorState::Destroy);
        lifetime = 0.0f;
    }
    for(int i = 0; i < (int)(unsigned)GetGame()->mAsteroids.size(); i++){
        Vector2 temp = GetGame()->mAsteroids[i]->GetPosition() - this->GetPosition();
        float distance = sqrt(temp.x*temp.x + temp.y*temp.y);
        if(distance <= 70.0f){
            GetGame()->mAsteroids[i]->SetState(ActorState::Destroy);
            this->SetState(ActorState::Destroy);
        }
    }
}
