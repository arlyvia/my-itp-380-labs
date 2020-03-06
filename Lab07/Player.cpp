//
//  Player.cpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/5/20.
//

#include "Player.hpp"
#include "Game.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "CollisionComponent.h"
#include "PlayerMove.hpp"

Player::Player(class Game* game)
:Actor(game)
{
    player_mhc = new MeshComponent(this);
    player_mhc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Ship.gpmesh"));
    
    player_cc = new CollisionComponent(this);
    player_cc->SetSize(100, 40, 60);
    
    player_move = new PlayerMove(this);
}
