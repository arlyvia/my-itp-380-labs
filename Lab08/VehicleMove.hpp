//
//  VehicleMove.hpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/24/20.
//

#ifndef VehicleMove_hpp
#define VehicleMove_hpp

#include <stdio.h>
#include "Component.h"
#include "Math.h"

class VehicleMove : public Component
{
public:
    VehicleMove(class Actor* owner);
    ~VehicleMove();
    
    void Update(float deltaTime) override;
    
    //member variables for arcade physics, update
    bool mPressed = false;
    void SetPressed(bool pressed) { mPressed = pressed; }
    
    enum Turn
    {
        Left,
        Right,
        None
    };
    
    Turn mTurn = None;
    void SetTurn(Turn turn) { mTurn = turn; }
    
    Vector3 mVelocity = Vector3(0,0,0);
    
    float mAngularVelocity = 0.0f;
    
    float mDriveTimer = 0.0f;
    
    //member variables for driving behavior
    float minLinAccelMag = 1000.0f;
    float maxLinAccelMag = 2500.0f;
    float accelRampTime = 2.0f;
    float angularAccel = 5 * Math::Pi;
    float linDragCoeff = 0.9f;
    float linDragCoeffPressed = 0.975f;
    float angularDragCoeff = 0.9f;
};

#endif /* VehicleMove_hpp */
