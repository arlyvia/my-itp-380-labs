//
//  Block.cpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/11/20.
//

#include "Block.hpp"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "Player.hpp"

Block::Block(class Game* game)
:Actor(game)
{
    this->GetGame()->AddBlock(this);
    
    block_mhc = new MeshComponent(this);
    block_mhc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    
    block_cc = new CollisionComponent(this);
    block_cc->SetSize(1, 1, 1);
}

Block::~Block()
{
    this->GetGame()->RemoveBlock(this);
}

void Block::OnUpdate(float deltaTime){
    if(GetGame()->mPlayer->GetPosition().x - GetPosition().x > 2000.0f){
        SetState(ActorState::Destroy);
    }
}

void Block::explode(){
    Vector3 original_block_pos = this->GetPosition();
    GetGame()->RemoveBlock(this);
    SetState(ActorState::Destroy);
    
    std::vector<Block*> toDestroy;
    
    for(int i = 0; i < (int)(unsigned)GetGame()->mBlocks.size(); i++){
        Vector3 temp = original_block_pos - GetGame()->mBlocks[i]->GetPosition();
        float distance = sqrt(temp.x*temp.x + temp.y*temp.y + temp.z*temp.z);
        if(distance <= 50.0f){
            toDestroy.push_back(GetGame()->mBlocks[i]);
        }
    }
    
    for(int i=0; i < (int)(unsigned)toDestroy.size(); i++){
        if(toDestroy[i]->mExploding == true){
            toDestroy[i]->explode();
        } else {
            toDestroy[i]->SetState(ActorState::Destroy);
            GetGame()->RemoveBlock(toDestroy[i]);
        }
    }
}

