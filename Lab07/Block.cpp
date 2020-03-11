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
    block_mhc->SetTextureIndex(2);
    
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

