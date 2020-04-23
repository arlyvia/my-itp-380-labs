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
#include <iostream>

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
    
    mPitchMatrix = Matrix4::CreateRotationY(mPitchAngle);
    mYawMatrix = Matrix4::CreateRotationZ(mOwner->GetRotation());
    
    //camera rotation
    mRollAngle += mRollSpeed * deltaTime;
    std::cout << "rollsp " << mRollSpeed << std::endl;
    
    /*if (mRollAngle >= Math::PiOver2/2.0f)
    {
        mRollAngle = Math::PiOver2/2.0f;
    } else if (mRollAngle <= -Math::PiOver2/2.0f)
    {
        mRollAngle = -Math::PiOver2/2.0f;
    }*/
    
    CollSide side = mOwner->GetGame()->mPlayer->player_move->GetWallRunSide();
    
    
    if(side == CollSide::SideMinX || side == CollSide::SideMaxY){
        mRollAngle = Math::Clamp(mRollAngle, -Math::Pi / 6.0f, 0.0f);
    } else {
        //0 to pi/6
        mRollAngle = Math::Clamp(mRollAngle, 0.0f, Math::Pi / 6.0f);
    }
    
    Matrix4 rollMatrix;
    if(side == CollSide::SideMaxY || side == CollSide::SideMinY){
        rollMatrix = Matrix4::CreateRotationX(mRollAngle);
    } else {
        rollMatrix = Matrix4::CreateRotationY(mRollAngle);
    }
    
    mRotationMatrix =  mPitchMatrix * mYawMatrix;
    
    Vector3 transform_vec = Vector3(1, 0, 0);
    
    Vector3 camera_forward = Vector3::Transform(transform_vec, mRotationMatrix);
    
    Vector3 targetPos = mOwner->GetPosition() + (camera_forward * TargetDist);
    
    Vector3 transform_vec2 = Vector3(0, 0, 1);
    
    Vector3 camera_up = Vector3::Transform(transform_vec2, rollMatrix);
    
    Matrix4 viewMatrix = Matrix4::CreateLookAt(mOwner->GetPosition(),targetPos, camera_up);
    
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);
}

/*Vector3 CameraComponent::idealPos(){
    Vector3 idealPos = mOwner->GetPosition() - (mOwner->GetForward() * HDist) +
        (Vector3::UnitZ * 70.0f);
    return idealPos;
}*/



