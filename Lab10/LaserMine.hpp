//
//  LaserMine.hpp
//  Lab10
//
//  Created by Arlyvia Chaialee on 4/15/20.
//

#ifndef LaserMine_hpp
#define LaserMine_hpp

#include <stdio.h>
#include "Actor.h"

class LaserMine: public Actor {
    public:
        //constructor
        LaserMine(class Game* game, Actor* parent);
    
        class MeshComponent* laserMine_mc;
        class LaserComponent* laser_lc;
};

#endif /* LaserMine_hpp */
