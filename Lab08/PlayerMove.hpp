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
#include "VehicleMove.hpp"

class PlayerMove: public VehicleMove {
    public:
        PlayerMove(class Actor* owner);
    
        //void ProcessInput(const Uint8* keyState) override;
        void ProcessInput(const Uint8* keyState)override;
        void Update(float deltaTime) override;
    
        void OnLapChange(int newLap) override;
    
        VehicleMove* player_vm;
    
        //int GetLapNum();

        //Vector3 mVelocity;
        //float x_speed = 400.0f;
        //float z_speed = 300.0f;
        //float y_speed = 300.0f;
    
        //Vector3 mPos = mOwner->GetPosition();
        //float zDir = 0;
        //float yDir = 0;
    
};

#endif /* PlayerMove_hpp */
