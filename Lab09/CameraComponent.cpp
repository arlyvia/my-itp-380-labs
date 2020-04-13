//
//  CameraComponent.cpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/25/20.
//

#include "CameraComponent.hpp"
#include "Actor.h"
#include "Renderer.h"
#include "Game.h"

CameraComponent::CameraComponent(class Actor* owner)
:Component(owner)
{
    
}

void CameraComponent::Update(float deltaTime)
{
    mPitchAngle = mPitchSpeed * deltaTime;
    
    if (mPitchAngle >= Math::PiOver2/2.0f)
    {
        mPitchAngle = Math::PiOver2/2.0f;
    } else if (mPitchAngle <= -Math::PiOver2/2.0f)
    {
        mPitchAngle = -Math::PiOver2/2.0f;
    }
    
    mPitchMatrix = Matrix4::CreateRotationY(mPitchAngle);
    mYawMatrix = Matrix4::CreateRotationZ(mOwner->GetRotation());
    
    mRotationMatrix =  mPitchMatrix * mYawMatrix;
    
    Vector3 transform_vec = Vector3(1, 0, 0);
    
    Vector3 camera_forward = Vector3::Transform(transform_vec, mRotationMatrix);
    
    Vector3 targetPos = mOwner->GetPosition() + (camera_forward * TargetDist);
    
    Matrix4 viewMatrix = Matrix4::CreateLookAt(mOwner->GetPosition(),targetPos, Vector3::UnitZ);
    
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);
    
}

/*Vector3 CameraComponent::idealPos(){
    Vector3 idealPos = mOwner->GetPosition() - (mOwner->GetForward() * HDist) +
        (Vector3::UnitZ * 70.0f);
    return idealPos;
}*/



