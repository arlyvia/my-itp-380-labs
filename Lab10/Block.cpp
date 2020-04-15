//
//  Block.cpp
//  Lab09
//
//  Created by Arlyvia Chaialee on 3/31/20.
//

#include "Block.hpp"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "Actor.h"
#include "Renderer.h"

Block::Block(class Game* game)
:Actor(game)
{
    SetScale(64.0f);
    
    block_mc = new MeshComponent(this);
    block_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    
    block_cc = new CollisionComponent(this);
    block_cc->SetSize(1.0f, 1.0f, 1.0f);
    
    GetGame()->mBlocks.push_back(this);
}

Block::~Block()
{
    auto iter = std::find(GetGame()->mBlocks.begin(), GetGame()->mBlocks.end(), this);
    if (iter != GetGame()->mBlocks.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        auto iter2 = GetGame()->mBlocks.end() - 1;
        std::iter_swap(iter, iter2);
        GetGame()->mBlocks.pop_back();
    }
}
