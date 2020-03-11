//
//  SideBlock.cpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/7/20.
//

#include "SideBlock.hpp"
#include "Actor.h"
#include "Game.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Player.hpp"

SideBlock::SideBlock(class Game* game)
:Actor(game)
{
    sideblock_mhc = new MeshComponent(this);
    sideblock_mhc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    
    //player_cc = new CollisionComponent(this);
    //player_cc->SetSize(100, 40, 60);
    
    //player_move = new PlayerMove(this);
}

void SideBlock::OnUpdate(float deltaTime){
    if(GetGame()->mPlayer->GetPosition().x - GetPosition().x > 2000.0f){
        SetState(ActorState::Destroy);
    }
}
