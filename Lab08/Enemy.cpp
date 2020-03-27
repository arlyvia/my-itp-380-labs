//
//  Enemy.cpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/26/20.
//

#include "Enemy.hpp"
#include "Game.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "EnemyMove.hpp"

Enemy::Enemy(class Game* game)
:Actor(game)
{
    enemy_mhc = new MeshComponent(this);
    enemy_mhc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Kart.gpmesh"));
    enemy_mhc->SetTextureIndex(6);
    SetScale(0.75f);
    
    enemy_move = new EnemyMove(this);
}
