//
//  Asteroid.hpp
//  Lab02
//
//  Created by Arlyvia Chaialee on 2/3/20.
//

#ifndef Asteroid_hpp
#define Asteroid_hpp

#include <stdio.h>

#endif /* Asteroid_hpp */

#include "Actor.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

class Asteroid: public Actor {
    public:
        //constructor
        Asteroid(class Game* game);
    
        //destructor
        ~Asteroid();
    
        //member variables
        int mDirection = 0;
        SpriteComponent* asteroid_sc;
        MoveComponent* asteroid_mc;
        void OnUpdate(float deltaTime) override;
    
        //methods
        //void OnProcessInput(const Uint8* keyState) override;
};
