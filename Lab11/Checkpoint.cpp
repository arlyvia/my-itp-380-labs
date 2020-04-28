//
//  Checkpoint.cpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#include "Checkpoint.hpp"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Player.hpp"

Checkpoint::Checkpoint(class Game* game, class Actor* parent)
:Actor(game, parent)
{
    checkpoint_mc = new MeshComponent(this);
    checkpoint_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Checkpoint.gpmesh"));
    
    checkpoint_cc = new CollisionComponent(this);
    checkpoint_cc->SetSize(25.0f, 25.0f, 25.0f);
}


void Checkpoint::OnUpdate(float deltaTime){
    
    GetGame()->mCheckpoints.front()->checkpoint_mc->SetTextureIndex(0);
    
    if(checkpoint_cc->Intersect(GetGame()->mPlayer->player_coc)){
        if(!mLevelString.empty()){
            GetGame()->SetNextLevel(mLevelString);
        }
        
        GetGame()->mPlayer->SetRespawn(GetGame()->mCheckpoints.front()->GetPosition());
        GetGame()->mCheckpoints.front()->SetState(ActorState::Destroy);
        GetGame()->mCheckpoints.pop();
        if(!GetGame()->mCheckpoints.empty()){
            GetGame()->mCheckpoints.front()->SetState(ActorState::Active);
            
        }
        
    }
    
    
}
