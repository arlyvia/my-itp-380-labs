//
//  Bullet.cpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/12/20.
//

#include "Bullet.hpp"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "MoveComponent.h"
#include "Player.hpp"
#include "Block.hpp"

Bullet::Bullet(class Game* game)
:Actor(game)
{
    bullet_mhc = new MeshComponent(this);
    bullet_mhc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
    
    bullet_mc = new MoveComponent(this);
    bullet_mc->SetForwardSpeed(900.0f);
    
    bullet_cc = new CollisionComponent(this);
    bullet_cc->SetSize(10, 10, 10);
}

void Bullet::OnUpdate(float deltaTime){
    
    lifetime = deltaTime + lifetime;
    if(lifetime > 1.0f){
        SetState(ActorState::Destroy);
        lifetime = 0.0f;
    }
    for(int i = 0; i < (int)(unsigned)GetGame()->mBlocks.size(); i++){
        if(GetComponent<CollisionComponent>()->Intersect(GetGame()->mBlocks[i]->GetComponent<CollisionComponent>())){
                SetState(ActorState::Destroy);
                if(GetGame()->mBlocks[i]->mExploding == true){
                    GetGame()->mBlocks[i]->explode();
                }
        }
    }
}



