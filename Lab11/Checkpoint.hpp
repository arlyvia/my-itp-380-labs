//
//  Checkpoint.hpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#ifndef Checkpoint_hpp
#define Checkpoint_hpp

#include <stdio.h>
#include "Actor.h"
#include <string>

class Checkpoint: public Actor {
    public:
        //constructor
        Checkpoint(class Game* game, Actor* parent);
    
        void OnUpdate(float deltaTime);
        
        class MeshComponent* checkpoint_mc;
    
        class CollisionComponent* checkpoint_cc;
    
        bool active = false;
    
        std::string mLevelString = "";
        void SetLevelString(std::string levelString) { mLevelString = levelString; }
};


#endif /* Checkpoint_hpp */
