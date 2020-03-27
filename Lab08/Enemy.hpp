//
//  Enemy.hpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/26/20.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "Actor.h"
#include "Math.h"

class Enemy: public Actor {
    public:
        //constructor
        Enemy(class Game* game);
        
        class MeshComponent* enemy_mhc;
        class EnemyMove* enemy_move;
    
        std::vector<Vector3>
};


#endif /* Enemy_hpp */
