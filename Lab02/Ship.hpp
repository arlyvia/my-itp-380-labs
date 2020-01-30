//
//  Ship.hpp
//  Lab02
//
//  Created by Arlyvia Chaialee on 1/29/20.
//

#ifndef Ship_hpp
#define Ship_hpp

#include <stdio.h>
#include "Actor.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

#endif /* Ship_hpp */

class Ship: public Actor {
    public:
        //constructor
        Ship(class Game* game);
        
    
        //member variables
        int mDirection = 0;
        SpriteComponent* ship_sc;
        MoveComponent* ship_mc;
    //        void OnUpdate(float deltaT*ime) override;
    
        //methods
        void OnProcessInput(const Uint8* keyState) override;
};
