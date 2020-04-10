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
    
    float HDist = 60.0f;
    //float VDist = 70.0f;
    float TargetDist = 50.0f;
    float SpringConstant = 256.0f;
    float DampeningConstant = 0.0f;
    Vector3 CameraPos = idealPos();
    Vector3 CameraVelocity = Vector3(0,0,0);
    
    void SnapToIdeal();
};

#endif /* CameraComponent_hpp */
