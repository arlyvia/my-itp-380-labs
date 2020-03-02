//
//  Key.hpp
//  Lab05
//
//  Created by Arlyvia Chaialee on 3/2/20.
//

#ifndef Key_hpp
#define Key_hpp

#include <stdio.h>
#include "Actor.h"

class Key: public Actor {
    public:
        //constructor
        Key(class Game* game);
        class CollisionComponent* key_cc;
        class SpriteComponent* key_sc;
};

#endif /* Key_hpp */
