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

SecurityCamera::~SecurityCamera(){
    if(securityCamera_sco->mMotorChannel != -1){
        Mix_HaltChannel(securityCamera_sco->mMotorChannel);
    }
}

void SecurityCamera::OnUpdate(float deltaTime){
    if(mPauseTimer > 0.0f){
        mPauseTimer -= deltaTime;
        return;
    }
    while(securityCamera_sco->GetComponent<MeshComponent>()->GetTextureIndex() != 0){
        return;
    }
    mSlerpTimer += deltaTime;
    if(mSlerpTimer > mInterpTime){
        //Mix_HaltChannel(securityCamera_sco->mMotorChannel);
        //securityCamera_sco->mMotorChannel = -1;
        //Mix_Chunk* motor_sound = GetGame()->GetSound("Assets/Sounds/CameraMotor.wav");
        //securityCamera_sco->mMotorStopChannel = Mix_GroupAvailable(1);
        
        if(securityCamera_sco->mDistDot > 1500.0f){
            Mix_Volume(securityCamera_sco->mMotorChannel, 0);
        } else if(securityCamera_sco->mDistDot <= 1500.0f || securityCamera_sco->mDistDot > 500.0f){
            float x = securityCamera_sco->mDistDot / 128.0f;
            float vol = Math::Lerp(1500.0f, 500.0f, x);
            Mix_Volume(securityCamera_sco->mMotorChannel, (int)vol);
        } else if(securityCamera_sco->mDistDot <= 500.0f){
            Mix_Volume(securityCamera_sco->mMotorChannel, 128.0f);
        }
        
        /*if(Mix_PlayChannel(Mix_GroupAvailable(1), motor_sound, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }*/
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
