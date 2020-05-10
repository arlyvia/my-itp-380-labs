//
//  SecurityCone.hpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#ifndef SecurityCone_hpp
#define SecurityCone_hpp

#include <stdio.h>
#include "Actor.h"

class SecurityCone: public Actor {
    public:
        //constructor
        SecurityCone(class Game* game, Actor* parent);
    
        void OnUpdate(float deltaTime);
        
        class MeshComponent* securityCone_mc;
    
        class CollisionComponent* securityCone_cc;

        bool mInCone = false;
        void coneHelper();
        float mConeTimer = true;
    
        float mHeight = 300.0f;
        float mHalfAngle = Math::Pi / 6.0f;
    
        int mSecChannel = 0;
        bool mColorChange = false;
        
        int mMotorChannel = 0;
        int mMotorStopChannel = 0;
        
        float mDistDot = 0;
};

#endif /* SecurityCone_hpp */
