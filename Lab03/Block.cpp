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
   
}


void Block::changeTexture(std::string filename){
    this->block_sc->SetTexture(GetGame()->GetTexture(filename));
}
