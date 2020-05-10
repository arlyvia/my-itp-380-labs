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
    
    //working on
    /*Mix_Chunk* motor_sound = GetGame()->GetSound("Assets/Sounds/CameraMotor.wav");
    mMotorChannel = Mix_GroupAvailable(1);
    
    if(Mix_PlayChannel(Mix_GroupAvailable(1), motor_sound, -1)==-1) {
        printf("Mix_PlayChannel: %s\n",Mix_GetError());
    }*/
    
    if(mInCone){
        Mix_HaltChannel(mMotorChannel);
        mMotorChannel = -1;
        Mix_Chunk* motor_stop_sound = GetGame()->GetSound("Assets/Sounds/CameraMotorStop.wav");
        if(Mix_PlayChannel(Mix_GroupAvailable(1), motor_stop_sound, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
        //yellow
        securityCone_mc->SetTextureIndex(1);
        Mix_Chunk* sec_sound = GetGame()->GetSound("Assets/Sounds/SecurityDetected.wav");
        mSecChannel = Mix_GroupAvailable(1);
        if(Mix_PlayChannel(Mix_GroupAvailable(1), sec_sound, 0)==-1) {
            printf("Mix_PlayChannel: %s\n",Mix_GetError());
        }
        mColorChange = true;
        mConeTimer += deltaTime;
        if(mConeTimer > 2.0f){
            //red
            securityCone_mc->SetTextureIndex(2);
            mColorChange = true;
            if(mConeTimer > 2.50f){
                GetGame()->mPlayer->SetState(ActorState::Paused);
            }
        }
    } else {
        mConeTimer = 0;
        securityCone_mc->SetTextureIndex(0);
        if(mColorChange){
            Mix_HaltChannel(mSecChannel);
            mColorChange = false;
        }
    }
    
}

void SecurityCone::coneHelper(){
    //call in update eventually
    Vector3 CP = GetGame()->mPlayer->GetPosition() - GetWorldPosition();
    
    mDistDot = Vector3::Dot(CP, GetWorldForward());
    
    if(mDistDot > 1500.0f){
        Mix_Volume(mMotorChannel, 0);
    } else if(mDistDot <= 1500.0f || mDistDot > 500.0f){
        float x = mDistDot / 128.0f;
        float vol = Math::Lerp(1500.0f, 500.0f, x);
        Mix_Volume(mMotorChannel, (int)vol);
    } else if(mDistDot <= 500.0f){
        Mix_Volume(mMotorChannel, 128.0f);
    }
    
    Vector3 CP_norm = Vector3::Normalize(CP);

    float CP_angle = Math::Acos(Vector3::Dot(GetWorldForward(), CP_norm));
  
    if(mDistDot <= mHeight && CP_angle <= mHalfAngle){
        mInCone = true;
    } else {
        mInCone = false;
    }
}
