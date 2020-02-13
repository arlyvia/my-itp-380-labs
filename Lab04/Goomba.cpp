//
//  Goomba.cpp
//  Lab04
//
//  Created by Arlyvia Chaialee on 2/12/20.
//

#include "Goomba.hpp"
#include "Game.h"

Goomba::Goomba(class Game* game)
:Actor(game)
{
    this->goomba_sc = new SpriteComponent(this);
    this->goomba_sc->SetTexture(this->GetGame()->GetTexture("Assets/Goomba/Walk0.png"));
    this->goomba_sc->SetDrawOrder(150);
    
    this->goomba_cc = new CollisionComponent(this);
    this->goomba_cc->SetSize(32.0f, 32.0f);
    
    this->goomba_move = new GoombaMove(this);
}

void Goomba::OnUpdate(float deltaTime){
    if(this->stomped){
        this->deadCounter += deltaTime;
        
        if(this->deadCounter>=0.25f){
            auto it = std::find(this->GetGame()->mEnemies.begin(), this->GetGame()->mEnemies.end(),this);
            if(it != this->GetGame()->mEnemies.end())
            {
                this->GetGame()->mEnemies.erase(it);
            }
            this->SetState(ActorState::Destroy);
        }
    }
    
}

void Goomba::stomp(){
    this->stomped=true;
    this->goomba_move->stomped = true;
    this->goomba_sc->SetTexture(this->GetGame()->GetTexture("Assets/Goomba/Dead.png"));
    
    this->goomba_cc->~CollisionComponent();
}

