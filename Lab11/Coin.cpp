//
//  Coin.cpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#include "Coin.hpp"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "SecurityCone.hpp"
#include "Player.hpp"

Coin::Coin(class Game* game, class Actor* parent)
:Actor(game, parent)
{
    coin_mc = new MeshComponent(this);
    coin_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Coin.gpmesh"));
    
    coin_cc = new CollisionComponent(this);
    coin_cc->SetSize(100.0f, 100.0f, 100.0f);
}

void Coin::OnUpdate(float deltaTime){
    SetRotation(GetRotation()  + Math::Pi * deltaTime);
    
    if(coin_cc->Intersect(GetGame()->mPlayer->player_coc)){
        Mix_Chunk* coin_sound = GetGame()->GetSound("Assets/Sounds/Coin.wav");
        if(Mix_PlayChannel(-1, coin_sound, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
        SetState(ActorState::Destroy);
    }
}
