//
//  Laser.hpp
//  Lab02
//
//  Created by Arlyvia Chaialee on 2/3/20.
//

#ifndef Laser_hpp
#define Laser_hpp

#include <stdio.h>

#include "Actor.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

#endif /* Laser_hpp */

class Laser: public Actor {
    public:
        //constructor
        Laser(class Game* game);
        
    
        //member variables
        int mDirection = 0;
        SpriteComponent* laser_sc;
        MoveComponent* laser_mc;
        float lifetime = 0;
    
        void OnUpdate(float deltaTime) override;
        
};
