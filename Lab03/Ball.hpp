//
//  Ball.hpp
//  Lab03
//
//  Created by Arlyvia Chaialee on 2/5/20.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include "Actor.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "Math.h"

#endif /* Ball_hpp */

class Ball: public Actor {
    public:
        //constructor
        Ball(class Game* game);
    
        //member variables
        SpriteComponent* ball_sc;
        CollisionComponent* ball_cc;
    
};
