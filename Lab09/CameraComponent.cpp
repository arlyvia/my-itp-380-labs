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
    //CameraPos += CameraVelocity * deltaTime;
    
    //Vector3 targetPos = mOwner->GetPosition() + (mOwner ->GetForward() * TargetDist);
    
    Matrix4 viewMatrix = Matrix4::CreateLookAt(mOwner->GetPosition(), mOwner ->GetForward() * TargetDist, Vector3::UnitZ);
    
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);
}

/*Vector3 CameraComponent::idealPos(){
    Vector3 idealPos = mOwner->GetPosition() - (mOwner->GetForward() * HDist) +
        (Vector3::UnitZ * 70.0f);
    return idealPos;
}*/



