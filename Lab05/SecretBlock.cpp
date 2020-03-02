//
//  SecretBlock.cpp
//  Lab05
//
//  Created by Arlyvia Chaialee on 2/27/20.
//

#include "SecretBlock.hpp"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Actor.h"

SecretBlock::SecretBlock(class Game* game)
:Actor(game){
    secretBlock_cc = new CollisionComponent(this);
    secretBlock_cc->SetSize(32.0f, 32.0f);
    secretBlock_sc = new SpriteComponent(this);
    secretBlock_sc->SetTexture(GetGame()->GetTexture("Assets/SecretBlock.png"));
}
