//
//  SecurityCamera.cpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#include "SecurityCamera.hpp"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "SecurityCone.hpp"
#include "Player.hpp"

SecurityCamera::SecurityCamera(class Game* game, class Actor* parent)
:Actor(game, parent)
{
    securityCamera_mc = new MeshComponent(this);
    securityCamera_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Camera.gpmesh"));
    
    securityCamera_cc = new CollisionComponent(this);
    securityCamera_cc->SetSize(25.0f, 25.0f, 25.0f);
    
    securityCamera_sco = new SecurityCone(game, this);
}

void SecurityCamera::OnUpdate(float deltaTime){
    if(mPauseTimer > 0.0f){
        mPauseTimer -= deltaTime;
        return;
    }
    mSlerpTimer += deltaTime;
    if(mSlerpTimer > mInterpTime){
        mSlerpTimer = 0.0f;
        mPauseTimer += deltaTime;
        if(forwardSwing){
            forwardSwing = false;
        } else {
            forwardSwing = true;
        }
        return;
    }
    float t = mSlerpTimer / mInterpTime;
    if(forwardSwing){
        SetQuaternion(Quaternion::Slerp(mStartQ, mEndQ, t));
    } else {
        SetQuaternion(Quaternion::Slerp(mEndQ, mStartQ, t));
    }
}
