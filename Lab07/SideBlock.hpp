//
//  SideBlock.hpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/7/20.
//

#ifndef SideBlock_hpp
#define SideBlock_hpp

#include <stdio.h>
#include "Actor.h"

class SideBlock: public Actor {
    public:
        //constructor
        SideBlock(class Game* game);
        
        float mScale = 500.0f;
        class MeshComponent* sideblock_mhc;
        
        void OnUpdate(float deltaTime) override;
};

#endif /* SideBlock_hpp */
