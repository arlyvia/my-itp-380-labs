//
//  Player.hpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/5/20.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Actor.h"

class Player: public Actor {
    public:
        //constructor
        Player(class Game* game, Actor* parent);
        
        class PlayerMove* player_move;
        class CameraComponent* player_cc;
        class CollisionComponent* player_coc;
        class Hud* player_h;
        
        Vector3 mRespawn = Vector3::Zero;
        void SetRespawn(Vector3 respawn) { mRespawn = respawn; }
};

#endif /* Player_hpp */
