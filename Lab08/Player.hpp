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
        Player(class Game* game);
        
        class MeshComponent* player_mhc;
        class PlayerMove* player_move;
        class CameraComponent* player_cc;
        class PlayerUI* player_ui;
};

#endif /* Player_hpp */
