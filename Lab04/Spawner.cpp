//
//  Spawner.cpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#include "Spawner.hpp"
#include "Goomba.hpp"
#include "Game.h"
#include "Player.hpp"

Spawner::Spawner(class Game* game)
:Actor(game)
{

}

void Spawner::OnUpdate(float deltaTime){
    if(this->GetPosition().x - this->GetGame()->mPlayer->GetPosition().x < 600.0f){
        Goomba* goomba = new Goomba(this->GetGame());
        goomba->SetPosition(this->GetPosition());
        this->GetGame()->mEnemies.push_back(goomba);
        this->SetState(ActorState::Destroy);
    }
}
