//
//  EnemyMove.cpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/26/20.
//

#include "EnemyMove.hpp"

EnemyMove::EnemyMove(class Actor* owner)
:VehicleMove(owner)
{
   
}

void EnemyMove::Update(float deltaTime){
    VehicleMove::Update(deltaTime);
}
