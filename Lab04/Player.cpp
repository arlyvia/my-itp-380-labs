//
//  Player.cpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#include "Player.hpp"
#include "AnimatedSprite.h"
#include "Game.h"

Player::Player(class Game* game)
:Actor(game)
{
    this->player_ac = new AnimatedSprite(this);
    this->player_ac->SetTexture(this->GetGame()->GetTexture("Assets/Mario/Idle.png"));
    this->player_ac->SetDrawOrder(200);
    
    this->player_cc = new CollisionComponent(this);
    this->player_cc->SetSize(32.0f, 32.0f);
    
    this->player_move = new PlayerMove(this);
    
}

