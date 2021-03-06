//
//  Block.hpp
//  Lab09
//
//  Created by Arlyvia Chaialee on 3/31/20.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "Actor.h"

class Block: public Actor {
    public:
        //constructor
        Block(class Game* game);
        ~Block();
        
        class MeshComponent* block_mc;
        class CollisionComponent* block_cc;
    
        bool mIsMirror = false;
        bool GetIsMirror()  { return mIsMirror; }
        bool SetIsMirror(bool isMirror) { return mIsMirror = isMirror; }
};

#endif /* Block_hpp */
