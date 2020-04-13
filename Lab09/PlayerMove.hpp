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
    Falling
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
    
        float mZSpeed = 0.0f;
        const float Gravity = -980.0f;
    
        CollSide FixCollision(class CollisionComponent* self, class CollisionComponent* block);
        bool ground = false;
        bool standing = false;
        bool hit_head = false;
    
        float JumpSpeed = 500.0f;
        bool last_frame = false;
};

#endif /* PlayerMove_hpp */
