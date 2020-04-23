//
//  CameraComponent.hpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/25/20.
//

#ifndef CameraComponent_hpp
#define CameraComponent_hpp

#include <stdio.h>
#include "Component.h"
#include "Math.h"

class CameraComponent : public Component
{
public:
    CameraComponent(class Actor* owner);

    // Update the camera component
    void Update(float deltaTime) override;
    
    //spring camera
     Vector3 idealPos();
    
    float TargetDist = 50.0f;
    
    float mPitchAngle = 0;
    float mPitchSpeed = 0;
    
    float GetPitchSpeed() const { return mPitchSpeed; }
    float SetPitchSpeed(float speed) { return mPitchSpeed = speed; }
    
    Matrix4 mPitchMatrix;
    Matrix4 mYawMatrix;
    Matrix4 mRotationMatrix;
    
    //rolling
    float mRollAngle = 0.0f;
    float mRollSpeed = 0.0f;
    
    float GetRollSpeed() const { return mRollSpeed; }
    float SetRollSpeed(float speed) { return mRollSpeed = speed; }
   
    //mRotationMatrix = Matrix4::CreateRotationZ(mRotation);
    //mPositionMatrix = Matrix4::CreateTranslation(mPosition);
    
    //mWorldTransform = mScaleMatrix * mRotationMatrix * mPositionMatrix;
};

#endif /* CameraComponent_hpp */
