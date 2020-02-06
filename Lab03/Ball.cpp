//
//  Ball.cpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 2/5/20.
//

#include "Ball.hpp"

Ball::Ball(class Game* game)
    :Actor(game)
{
    this->ball_sc = new SpriteComponent(this);
    this->ball_sc->SetTexture(GetGame()->GetTexture("Assets/Ball.png"));
}
