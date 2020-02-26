//
//  Player.hpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "Actor.h"
#include "PlayerMove.hpp"

class Player: public Actor {
    public:
        //constructor
        Player(class Game* game);
    
        //member variables
        class AnimatedSprite* player_ac;
        CollisionComponent* player_cc;
    
        PlayerMove* player_move;
};

#endif /* Player_hpp */
