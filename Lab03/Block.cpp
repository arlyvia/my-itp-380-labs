//
//  Block.cpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 1/30/20.
//

#include "Block.hpp"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <SDL2/SDL_image.h>

Block::Block(class Game* game)
:Actor(game)
{
    /*this->ship_sc = new SpriteComponent(this);
    this->ship_sc->SetTexture(GetGame()->GetTexture("Assets/Ship.png"));
    this->ship_mc = new MoveComponent(this);
    */
}


void Block::changeTexture(std::string filename){
    this->block_sc->SetTexture(GetGame()->GetTexture(filename));
}
