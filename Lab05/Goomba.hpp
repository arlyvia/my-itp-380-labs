//
//  Goomba.hpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#ifndef Goomba_hpp
#define Goomba_hpp

#include <stdio.h>
#include "SpriteComponent.h"
#include "GoombaMove.hpp"
#include "Actor.h"
#include "PlayerMove.hpp"
#include "CollisionComponent.h"

class Goomba: public Actor {
    public:
        //constructor
        Goomba(class Game* game);
    
        void OnUpdate(float deltaTime) override;
    
        void stomp();
    
        //member variables
        class AnimatedSprite* goomba_ac;
        //MoveComponent* goomba_mc;
        CollisionComponent* goomba_cc;
       
    
        GoombaMove* goomba_move;
        bool stomped = false;
        float deadCounter = 0;
    
};

#endif /* Player_hpp */
