//
//  Spawner.hpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#ifndef Spawner_hpp
#define Spawner_hpp

#include <stdio.h>
#include "Actor.h"


class Spawner: public Actor {
    public:
        //constructor
        Spawner(class Game* game);
        void OnUpdate(float deltaTime) override;
    
        float dist_btw_players = 600.0f;
    
};

#endif /* Spawner_hpp */
