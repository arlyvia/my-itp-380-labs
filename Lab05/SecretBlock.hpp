//
//  SecretBlock.hpp
//  Lab05
//
//  Created by Arlyvia Chaialee on 2/27/20.
//

#ifndef SecretBlock_hpp
#define SecretBlock_hpp

#include <stdio.h>
#include "CollisionComponent.h"
#include "Actor.h"


class SecretBlock: public Actor {
    public:
        //constructor
        SecretBlock(class Game* game);
        CollisionComponent* secretBlock_cc;
        class SpriteComponent* secretBlock_sc;
};


#endif /* SecretBlock_hpp */
