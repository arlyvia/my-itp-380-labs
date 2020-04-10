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

        void ProcessInput(const Uint8* keyState)override;
        void Update(float deltaTime) override;
};

#endif /* PlayerMove_hpp */