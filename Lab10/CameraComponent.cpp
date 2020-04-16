//
//  CameraComponent.cpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/25/20.
//

#include "CameraComponent.hpp"
#include "Actor.h"
#include "Renderer.h"
#include "Player.hpp"
#include "PlayerMove.hpp"
#include "Game.h"

CameraComponent::CameraComponent(class Actor* owner)
:Component(owner)
{
    
}

void CameraComponent::Update(float deltaTime)
{
    mPitchAngle += mPitchSpeed * deltaTime;
    
    if (mPitchAngle >= Math::PiOver2/2.0f)
    {
        mPitchAngle = Math::PiOver2/2.0f;
    } else if (mPitchAngle <= -Math::PiOver2/2.0f)
    {
        mPitchAngle = -Math::PiOver2/2.0f;
    }
    
    mRollAngle += mRollSpeed * deltaTime;
    
    if (mRollAngle >= Math::PiOver2/2.0f)
    {
        mRollAngle = Math::PiOver2/2.0f;
    } else if (mRollAngle <= -Math::PiOver2/2.0f)
    {
        mRollAngle = -Math::PiOver2/2.0f;
    }
    
    mPitchMatrix = Matrix4::CreateRotationY(mPitchAngle);
    mYawMatrix = Matrix4::CreateRotationZ(mOwner->GetRotation());
    
    mRotationMatrix =  mPitchMatrix * mYawMatrix;
    
    Vector3 transform_vec = Vector3(1, 0, 0);
    
    Vector3 camera_forward = Vector3::Transform(transform_vec, mRotationMatrix);
    
    Vector3 targetPos = mOwner->GetPosition() + (camera_forward * TargetDist);
    
    Matrix4 viewMatrix = Matrix4::CreateLookAt(mOwner->GetPosition(),targetPos, Vector3::UnitZ);
    
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);
    
    //CollSide side = mOwner->GetGame()->mPlayer->player_move->mWallRunSide;
    /*Matrix4 rollMatrix;
    if(mOwner->GetGame()->mPlayer->player_move->GetWallRunSide() == CollSide::SideMinY || mOwner->GetGame()->mPlayer->player_move->GetWallRunSide() == CollSide::SideMaxY){
        rollMatrix = Matrix4::CreateRotationX(mRollAngle);
    } else {
        rollMatrix = Matrix4::CreateRotationY(mRollAngle);
    }*/
}

/*Vector3 CameraComponent::idealPos(){
    Vector3 idealPos = mOwner->GetPosition() - (mOwner->GetForward() * HDist) +
        (Vector3::UnitZ * 70.0f);
    return idealPos;
}*/



