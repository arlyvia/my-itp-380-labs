//
//  Coin.hpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#ifndef Coin_hpp
#define Coin_hpp

#include <stdio.h>
#include "Actor.h"

class Coin: public Actor {
    public:
        //constructor
        Coin(class Game* game, Actor* parent);
    
        void OnUpdate(float deltaTime) override;
        
        class MeshComponent* coin_mc;
    
        class CollisionComponent* coin_cc;
};

#endif /* Coin_hpp */
