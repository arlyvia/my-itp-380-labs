//
//  SecurityCamera.hpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#ifndef SecurityCamera_hpp
#define SecurityCamera_hpp

#include <stdio.h>
#include "Actor.h"

class SecurityCamera: public Actor {
    public:
        //constructor
        SecurityCamera(class Game* game, Actor* parent);
        ~SecurityCamera();
    
        //void OnUpdate(float deltaTime);
        
        class MeshComponent* securityCamera_mc;
    
        class CollisionComponent* securityCamera_cc;
    
        bool active = false;
    
        class SecurityCone* securityCamera_sco;
};


#endif /* SecurityCamera_hpp */
