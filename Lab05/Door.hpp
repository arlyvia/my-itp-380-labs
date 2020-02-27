//
//  Door.hpp
//  Lab05
//
//  Created by Arlyvia Chaialee on 2/26/20.
//

#ifndef Door_hpp
#define Door_hpp

#include <stdio.h>

#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include <string>

enum class DoorDirection
{
    Up,
    Down,
    Left,
    Right
};

enum class DoorState
{
    Open,
    Closed,
    Locked
};

class Door: public Actor {
    public:
        //constructor
        Door(class Game* game);
        CollisionComponent* door_cc;
        SpriteComponent* door_sc;
    
        DoorDirection mDirection;
        DoorState mState;
        std::string mDestination;
    
        void SetUpDoor(DoorDirection direction, DoorState state, std::string destination);
        void UpdateTexture(DoorDirection direction, DoorState state, std::string destination);
    
        
};

#endif /* Door_hpp */
