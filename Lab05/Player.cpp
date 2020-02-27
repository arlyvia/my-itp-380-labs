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
    //this->player_ac->SetTexture(this->GetGame()->GetTexture("Assets/Mario/Idle.png"));
    this->player_ac->SetDrawOrder(200);
    
    this->player_cc = new CollisionComponent(this);
    this->player_cc->SetSize(20.0f, 20.0f);
    
    this->player_move = new PlayerMove(this);
    
    std::vector<SDL_Texture*> walkUpAnim{
         GetGame()->GetTexture("Assets/Link/WalkUp0.png"),
         GetGame()->GetTexture("Assets/Link/WalkUp1.png")
    };
    
    std::vector<SDL_Texture*> walkDownAnim{
         GetGame()->GetTexture("Assets/Link/WalkDown0.png"),
         GetGame()->GetTexture("Assets/Link/WalkDown1.png")
    };
    
    std::vector<SDL_Texture*> walkLeftAnim{
            GetGame()->GetTexture("Assets/Link/WalkLeft0.png"),
            GetGame()->GetTexture("Assets/Link/WalkLeft1.png")
    };
    std::vector<SDL_Texture*> walkRightAnim{
            GetGame()->GetTexture("Assets/Link/WalkRight0.png"),
            GetGame()->GetTexture("Assets/Link/WalkRight1.png")
    };
    
    player_move->Player_Animate("walkUp", walkUpAnim);
    player_ac->SetIsPaused(true);
    /*player_ac->AddAnimation("walkUp", walkUpAnim);
    player_ac->AddAnimation("walkDown", walkDownAnim);
    player_ac->AddAnimation("walkLeft", walkLeftAnim);
    player_ac->AddAnimation("walkRight", walkRightAnim);
    
    player_ac->SetIsPaused(true);
    player_ac->SetAnimation("walkUp");*/
    
}

