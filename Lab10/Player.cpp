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
#include "CollisionComponent.h"
#include "Renderer.h"
#include "PlayerMove.hpp"

Player::Player(class Game* game, class Actor* parent)
:Actor(game, parent)
{
    player_move = new PlayerMove(this);
    
    player_cc = new CameraComponent(this);
    
    player_coc = new CollisionComponent(this);
    player_coc->SetSize(50.0f, 175.0f, 50.0f);
}
