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
#include "CollisionComponent.h"

enum class MoveState
{
    OnGround,
    Jump,
    Falling,
    WallClimb,
    WallRun
};

class PlayerMove: public MoveComponent {
    public:
        PlayerMove(class Actor* owner);

        void ProcessInput(const Uint8* keyState)override;
        void Update(float deltaTime) override;
    
        //state machine
        MoveState mCurrentState;
        void ChangeState(MoveState ms);
    
        void UpdateOnGround(float deltaTime);
        void UpdateJump(float deltaTime);
        void UpdateFalling(float deltaTime);
        void UpdateWallClimb(float deltaTime);
        void UpdateWallRun(float deltaTime);
    
        //float mZSpeed = 0.0f;
        //const float Gravity = -980.0f;
    
        CollSide FixCollision(class CollisionComponent* self, class CollisionComponent* block);
        bool ground = false;
        bool standing = false;
        bool hit_head = false;
    
        //float JumpSpeed = 500.0f;
        bool last_frame = false;
    
        //Forces
        Vector3 mVelocity;
        Vector3 mAcceleration;
        Vector3 mPendingForces;
    
        float mMass = 1.0f;
        Vector3 mGravity = Vector3(0.0f, 0.0f, -980.0f);
        Vector3 mJumpForce = Vector3(0.0f, 0.0f, 35000.0f);
    
        void PhysicsUpdate(float deltaTime);
        void AddForce(const Vector3& force);
    
        void FixXYVelocity();
    
        //Wall climbing
        bool CanWallClimb(CollSide side);
        Vector3 mClimbForce = Vector3(0.0f, 0.0f, 1800.0f);
        bool collide_side = false;
        float mWallClimbTimer = 0.0f;
    
        //Horizontal wall running
        Vector3 mWallRunForce = Vector3(0.0f, 0.0f, 1200.0f);
        float mWallRunTimer = 0.0f;
    
        bool CanWallRun(CollSide side);
        CollSide mSide;
        CollSide GetWallRunSide() { return mSide; }
};

#endif /* PlayerMove_hpp */
