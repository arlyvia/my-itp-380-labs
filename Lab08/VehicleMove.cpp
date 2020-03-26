//
//  VehicleMove.cpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/24/20.
//

#include "VehicleMove.hpp"
#include "Actor.h"
#include "Game.h"
#include "HeightMap.hpp"
#include <iostream>

VehicleMove::VehicleMove(class Actor* owner)
:Component(owner, 50)
{
   
}

VehicleMove::~VehicleMove(){}

void VehicleMove::Update(float deltaTime)
{
    mDriveTimer = mDriveTimer + deltaTime;
    
    float lerp = mDriveTimer/accelRampTime;
    
    if(mPressed){
        if (lerp > 1.0) lerp = 1.0f;
        float accelerationMagnitude = Math::Lerp(minLinAccelMag, maxLinAccelMag, lerp);
        mVelocity = mVelocity + mOwner->GetForward() * accelerationMagnitude * deltaTime;
    } else {
        mDriveTimer = 0.0f;
    }
    
    mOwner->SetPosition(mOwner->GetPosition() + mVelocity * deltaTime);
    
    int z_pos = Math::Lerp(mOwner->GetPosition().z, mOwner->GetGame()->mHeightMap->GetHeight(mOwner->GetPosition().x,
                                                                                              mOwner->GetPosition().y), 0.1f);
    
    if(mOwner->GetGame()->mHeightMap->IsOnTrack(mOwner->GetPosition().x, mOwner->GetPosition().y)){
        mOwner->SetPosition(Vector3(mOwner->GetPosition().x, mOwner->GetPosition().y, z_pos));
    }
       //bool HeightMap::IsOnTrack(float x, float y){
    
    if(mPressed){
       mVelocity = mVelocity * linDragCoeffPressed;
   } else {
       mVelocity = mVelocity * linDragCoeff;
   }
    
    if(mTurn == Turn::Left){
        mAngularVelocity = mAngularVelocity + angularAccel * -1.0f * deltaTime;
    } else if(mTurn == Turn::Right){
        mAngularVelocity = mAngularVelocity + angularAccel * 1.0f * deltaTime;
    }
    
    //angularAccel = angularAccel + mAngularVelocity * deltaTime;
    
    mAngularVelocity = mAngularVelocity * angularDragCoeff;
    mOwner->SetRotation(mOwner->GetRotation() + mAngularVelocity * deltaTime);
}
