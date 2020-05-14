//
//  Checkpoint.cpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#include "Checkpoint.hpp"
#include "MeshComponent.h"
#include "Game.h"
#include "Hud.hpp"
#include "Renderer.h"
#include "Player.hpp"
#include "Actor.h"
#include <iostream>

Checkpoint::Checkpoint(class Game* game, class Actor* parent)
:Actor(game, parent)
{
    checkpoint_mc = new MeshComponent(this);
    checkpoint_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Checkpoint.gpmesh"));
    
    checkpoint_cc = new CollisionComponent(this);
    checkpoint_cc->SetSize(25.0f, 25.0f, 25.0f);
}


void Checkpoint::OnUpdate(float deltaTime){
    //std::cout << "timer " << GetGame()->mCheckpointTimer << std::endl;
    
    GetGame()->mCheckpoints.front()->checkpoint_mc->SetTextureIndex(0);
    
    if(checkpoint_cc->Intersect(GetGame()->mPlayer->player_coc)){
        GetGame()->mPlayer->player_h->UpdateTextTexture(GetGame()->mCheckpoints.front()->GetCheckpointText());
        
        GetGame()->at_next_checkpoint = true;
        
        if(!mLevelString.empty()){
            GetGame()->SetNextLevel(mLevelString);
        }
        
        //GetGame()->mPlayer->SetRespawn(GetGame()->mCheckpoints.front()->GetPosition());
        //GetGame()->mCurrCheckpoint = GetGame()->mCheckpoints.front();
        //Hud::UpdateTextTexture(GetGame()->mCheckpoints.front()->GetCheckpointText());
        
        GetGame()->mCheckpoints.front()->SetState(ActorState::Destroy);
        GetGame()->mCheckpoints.pop();
        if(!GetGame()->mCheckpoints.empty()){
            GetGame()->mCheckpoints.front()->SetState(ActorState::Active);
            
        }
        
        
        
    }
    
    
}
