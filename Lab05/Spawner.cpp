//
//  Spawner.cpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#include "Spawner.hpp"
#include "Game.h"
#include "Player.hpp"
#include "SpriteComponent.h"
#include "Actor.h"
#include <unordered_map>
#include <string>

Spawner::Spawner(class Game* game)
:Actor(game)
{
    //spawner_cc = new CollisionComponent(this);
    //spawner_cc->SetSize(32.0f, 32.0f);
    spawner_sc = new SpriteComponent(this);
}

void Spawner::OnUpdate(float deltaTime){
    //std::vector<Spawner*> spawners = GetGame()->spawnerMap[GetGame()->currRoom];
    for (auto& x: GetGame()->spawnerMap) {
      if(GetGame()->currRoom == x.first){
         if(mType == "Key"){
             spawner_sc->SetTexture(GetGame()->GetTexture("Assets/Key.png"));
         }
      }
    }
}
