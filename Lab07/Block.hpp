//
//  Block.hpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/11/20.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "Actor.h"
#include "SideBlock.hpp"

class Block: public Actor {
    public:
        //constructor
        Block(class Game* game);
    
        ~Block();
        float mScale = 25.0f;
        class MeshComponent* block_mhc;
        class CollisionComponent* block_cc;
    
        void OnUpdate(float deltaTime) override;
    
        bool mExploding;
    
        void explode();
};

#endif /* Block_hpp */
