//
//  Player.cpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/5/20.
//

#include "Player.hpp"
#include "Game.h"
#include "MeshComponent.h"
#include "CameraComponent.hpp"
#include "Renderer.h"
#include "PlayerMove.hpp"

Player::Player(class Game* game)
:Actor(game)
{
    player_mhc = new MeshComponent(this);
    player_mhc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Kart.gpmesh"));
    SetScale(0.75f);
    
    player_move = new PlayerMove(this);
    
    player_cc = new CameraComponent(this);
    player_cc->SnapToIdeal();
}
