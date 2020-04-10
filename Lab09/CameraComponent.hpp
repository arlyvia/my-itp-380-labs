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
};

#endif /* CameraComponent_hpp */
