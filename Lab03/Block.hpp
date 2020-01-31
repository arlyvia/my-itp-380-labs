//
//  Block.hpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 1/30/20.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "Actor.h"
#include "Game.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

#endif /* Block_hpp */

class Block: public Actor {
    public:
        //constructor
        Block(class Game* game);
        
    
        //member variables
        int mDirection = 0;
        SpriteComponent* block_sc;
        MoveComponent* block_mc;
    
        //methods
        void changeTexture(std::string filename);
};
