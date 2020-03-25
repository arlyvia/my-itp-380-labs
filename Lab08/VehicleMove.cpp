//
//  VehicleMove.cpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/24/20.
//

#include "VehicleMove.hpp"
#include "Actor.h"
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
        std::cout << lerp << std::endl;
        mVelocity = mVelocity + mOwner->GetForward() * accelerationMagnitude * deltaTime;
    } else {
        mDriveTimer = 0.0f;
    }
    
    mPosition = mPosition + mVelocity * deltaTime;
    
    if(mPressed){
       mVelocity = mVelocity * linDragCoeffPressed;
   } else {
       mVelocity = mVelocity * linDragCoeff;
   }
    
    if(mTurn == Turn::Left){
        mAngularVelocity = mAngularVelocity + mAngularVelocity * -1.0f * deltaTime;
    } else if(mTurn == Turn::Right){
        mAngularVelocity = mAngularVelocity + mAngularVelocity * 1.0f * deltaTime;
    }
    
    angularAccel = angularAccel + mAngularVelocity * deltaTime;
    
    mAngularVelocity = mAngularVelocity * angularDragCoeff;
}
