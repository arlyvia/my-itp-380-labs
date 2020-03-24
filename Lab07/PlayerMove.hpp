//
//  PlayerMove.hpp
//  Lab07
//
//  Created by Arlyvia Chaialee on 3/5/20.
//

#ifndef PlayerMove_hpp
#define PlayerMove_hpp

#include <stdio.h>
#include "MoveComponent.h"
#include "Math.h"
#include "Actor.h"

class PlayerMove: public MoveComponent {
    public:
        PlayerMove(class Actor* owner);
    
        //void ProcessInput(const Uint8* keyState) override;
        void ProcessInput(const Uint8* keyState)override;
        void Update(float deltaTime) override;
    
        Vector3 mVelocity;
        float x_speed = 400.0f;
        float z_speed = 300.0f;
        float y_speed = 300.0f;
    
        Vector3 mPos = mOwner->GetPosition();
        float zDir = 0;
        float yDir = 0;
    
        float HDist = 300.0f;
        float VDist = 100.0f;
        float TargetDist = 20.0f;
    
        float last_x_pos = 0;
    
        float mElapsedTime = 0;
        float mSpeedTimer = 0;
    
        float speed_multiplier = 1.0f;
};

#endif /* PlayerMove_hpp */
