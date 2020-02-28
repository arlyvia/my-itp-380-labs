//
//  Door.cpp
//  Lab05
//
//  Created by Arlyvia Chaialee on 2/26/20.
//

#include "Door.hpp"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Actor.h"

Door::Door(class Game* game)
:Actor(game){
    door_cc = new CollisionComponent(this);
    door_sc = new SpriteComponent(this);
}

void Door::SetUpDoor(DoorDirection direction, DoorState state, std::string destination){
    mDestination = destination;
    if(direction == DoorDirection::Up){
        if(state == DoorState::Open){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/UpOpen.png"));
        } else if(state == DoorState::Closed){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/UpClosed.png"));
        } else if(state == DoorState::Locked){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/UpLocked.png"));
        }
    } else if(direction == DoorDirection::Down){
        if(state == DoorState::Open){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/DownOpen.png"));
        } else if(state == DoorState::Closed){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/DownClosed.png"));
        } else if(state == DoorState::Locked){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/DownLocked.png"));
        }
    } else if(direction == DoorDirection::Left){
        if(state == DoorState::Open){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/LeftOpen.png"));
        } else if(state == DoorState::Closed){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/LeftClosed.png"));
        } else if(state == DoorState::Locked){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/LeftLocked.png"));
        }
    } else if(direction == DoorDirection::Right){
        if(state == DoorState::Open){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/RightOpen.png"));
        } else if(state == DoorState::Closed){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/RightClosed.png"));
        } else if(state == DoorState::Locked){
            door_sc->SetTexture(GetGame()->GetTexture("Assets/Door/RightLocked.png"));
        }
    }
    if(mDirection == DoorDirection::Up
       || mDirection == DoorDirection::Down){
        door_cc->SetSize(30.0f, 64.0f);
    } else {
        door_cc->SetSize(64.0f, 30.0f);
    }
}

void Door::UpdateTexture(DoorDirection direction, DoorState state, std::string destination){}
