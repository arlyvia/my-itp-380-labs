//
//  Block.cpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 1/30/20.
//

#include "Block.hpp"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>

Block::Block(class Game* game)
:Actor(game)
{
    this->GetGame()->AddBlock(this);
    this->block_cc = new CollisionComponent(this);
    this->block_cc->SetSize(32.0f, 32.0f);
}

Block::~Block()
{
    this->GetGame()->RemoveBlock(this);
}

void Block::changeTexture(std::string filename){
    this->block_sc->SetTexture(GetGame()->GetTexture(filename));
    
    
}
