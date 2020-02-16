//
//  Block.hpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 1/30/20.
//

#pragma once
#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

class Block: public Actor {
    public:
        //constructor
        Block(class Game* game);
        ~Block();
    
        //member variables
        int mDirection = 0;
        SpriteComponent* block_sc;
        MoveComponent* block_mc;
        CollisionComponent* block_cc;
    
        //methods
        void changeTexture(std::string filename);
};
