//
//  Asteroid.cpp
//  Lab02
//
//  Created by Arlyvia Chaialee on 2/3/20.
//

#include "Asteroid.hpp"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Random.h"
#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>
#include <vector>

Asteroid::Asteroid(class Game* game)
:Actor(game)
{
    this->asteroid_sc = new SpriteComponent(this);
    this->asteroid_sc->SetTexture(GetGame()->GetTexture("Assets/Asteroid.png"));
    this->asteroid_mc = new MoveComponent(this);
    this->asteroid_mc->SetForwardSpeed(150.0f);
    this->SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
    this->SetPosition(Random::GetVector(Vector2(0, 0), Vector2(1024, 768)));
    mGame->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
    // TODO
    mGame->RemoveAsteroid(this);
}


void Asteroid::OnUpdate(float deltaTime){
    if(this->GetPosition().x < 0){
        this->SetPosition(Vector2(1022, this->GetPosition().y));
    }
    if(this->GetPosition().x > 1024){
        this->SetPosition(Vector2(2, this->GetPosition().y));
    }
    if(this->GetPosition().y < 0){
        this->SetPosition(Vector2(this->GetPosition().x, 766));
    }
    if(this->GetPosition().y > 768){
        this->SetPosition(Vector2(this->GetPosition().x, 2));
    }
}
