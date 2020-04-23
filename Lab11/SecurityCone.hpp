//
//  SecurityCone.hpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#ifndef SecurityCone_hpp
#define SecurityCone_hpp

#include <stdio.h>
#include "Actor.h"

class SecurityCone: public Actor {
    public:
        //constructor
        SecurityCone(class Game* game, Actor* parent);
    
        //void OnUpdate(float deltaTime);
        
        class MeshComponent* securityCone_mc;
    
        class CollisionComponent* securityCone_cc;
};

#endif /* SecurityCone_hpp */
