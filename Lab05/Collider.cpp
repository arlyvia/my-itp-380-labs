//
//  Collider.cpp
//  Lab05
//
//  Created by Arlyvia Chaialee on 2/26/20.
//

#include "Collider.hpp"

#include <stdio.h>

#include "CollisionComponent.h"
#include "Actor.h"

Collider::Collider(class Game* game, float w, float h)
:Actor(game){
    collider_cc = new CollisionComponent(this);
    SetDimensions(w, h);
}

void Collider::SetDimensions(float w, float h){
    collider_cc->SetSize(w, h);
}
