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
        Block(class Game* game, Actor* parent);
        ~Block();
        
        class MeshComponent* block_mc;
        class CollisionComponent* block_cc;
    
        bool mIsMirror = false;
        bool GetIsMirror()  { return mIsMirror; }
        bool SetIsMirror(bool isMirror) { return mIsMirror = isMirror; }
    
        bool mIsRotate = false;
        bool GetIsRotate() { return mIsRotate; }
        bool SetIsRotate(bool isRotate) { return mIsRotate = isRotate; }
    
        void OnUpdate(float deltaTime) override;
};

#endif /* Block_hpp */
