//
//  SecretBlock.cpp
//  Lab05
//
//  Created by Arlyvia Chaialee on 2/27/20.
//

#include "SecretBlock.hpp"
#include "CollisionComponent.h"
#include "Actor.h"

SecretBlock::SecretBlock(class Game* game)
:Actor(game){
    secretBlock_cc = new CollisionComponent(this);
}
