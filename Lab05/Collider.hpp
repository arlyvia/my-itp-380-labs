//
//  Collider.hpp
//  Lab05
//
//  Created by Arlyvia Chaialee on 2/26/20.
//

#ifndef Collider_hpp
#define Collider_hpp

#include <stdio.h>

#include "CollisionComponent.h"
#include "Actor.h"


class Collider: public Actor {
    public:
        //constructor
        Collider(class Game* game, float w, float h);
        void SetDimensions(float w, float h);
        CollisionComponent* collider_cc;
};

#endif /* Collider_hpp */
