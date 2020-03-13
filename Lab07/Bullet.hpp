//
//  Bullet.hpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/12/20.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "Actor.h"

class Bullet: public Actor {
    public:
        //constructor
        Bullet(class Game* game);
    
        //float mScale = 25.0f;
        class MeshComponent* bullet_mhc;
        class CollisionComponent* bullet_cc;
        class MoveComponent* bullet_mc;
    
        float lifetime = 0;
    
        void OnUpdate(float deltaTime) override;
};

#endif /* Bullet_hpp */
