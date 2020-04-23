//
//  Arrow.hpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#ifndef Arrow_hpp
#define Arrow_hpp

#include <stdio.h>
#include "Actor.h"

class Arrow: public Actor {
    public:
        //constructor
        Arrow(class Game* game, Actor* parent);
        
        void OnUpdate(float deltaTime);
        
        class MeshComponent* arrow_mc;
    
        Quaternion arrow_q;
        
        bool active = false;
};

#endif /* Arrow_hpp */
