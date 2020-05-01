//
//  SecurityCone.cpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#include "SecurityCone.hpp"
#include "Actor.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Renderer.h"
#include "Player.hpp"
#include "Game.h"
#include <iostream>

SecurityCone::SecurityCone(class Game* game, class Actor* parent)
:Actor(game, parent)
{
    securityCone_mc = new MeshComponent(this, true);
    securityCone_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Cone.gpmesh"));
    
    securityCone_cc = new CollisionComponent(this);
    
    SetPosition(Vector3(30.0f, 0.0f, 0.0f));
    SetScale(3.0f);
}

void SecurityCone::OnUpdate(float deltaTime){
    coneHelper();
    securityCone_mc->SetTextureIndex(0);
    
    if(mInCone){
        securityCone_mc->SetTextureIndex(1);
        mConeTimer += deltaTime;
        if(mConeTimer > 2.0f){
            securityCone_mc->SetTextureIndex(2);
            //GetGame()->mPlayer->SetState(ActorState::Paused);
        }
    } else {
        mConeTimer = 0;
        securityCone_mc->SetTextureIndex(0);
    }
    
}

void SecurityCone::coneHelper(){
    //call in update eventually
    Vector3 CP = GetGame()->mPlayer->GetPosition() - GetWorldPosition();
    
    float dist_dot = Vector3::Dot(CP, GetWorldForward());
    
    Vector3 CP_norm = Vector3::Normalize(CP);

    float CP_angle = Math::Acos(Vector3::Dot(GetWorldForward(), CP_norm));
  
    if(dist_dot <= mHeight && CP_angle <= mHalfAngle){
        std::cout << "inTrue" << std::endl;
        mInCone = true;
    } else {
        mInCone = false;
    }
}
