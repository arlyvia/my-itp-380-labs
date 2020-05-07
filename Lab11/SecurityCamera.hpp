//
//  SecurityCamera.hpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#ifndef SecurityCamera_hpp
#define SecurityCamera_hpp

#include <stdio.h>
#include "Actor.h"

class SecurityCamera: public Actor {
    public:
        //constructor
        SecurityCamera(class Game* game, Actor* parent);
        ~SecurityCamera();
    
        //void OnUpdate(float deltaTime);
        
        class MeshComponent* securityCamera_mc;
    
        class CollisionComponent* securityCamera_cc;
    
        bool active = false;
    
        class SecurityCone* securityCamera_sco;
    
        //camera rotating
        Quaternion mStartQ;
        void SetStartQ(Quaternion startQ) { mStartQ = startQ; }
        
        Quaternion mEndQ;
        void SetEndQ(Quaternion endQ) { mEndQ = endQ; }
    
        float mInterpTime;
        void SetInterpTime(float interpTime) { mInterpTime = interpTime; }
        
        float mPauseTime;
        void SetPauseTime(float pauseTime) { mPauseTime = pauseTime; }
    
        void OnUpdate(float deltaTime) override;
        float mSlerpTimer = 0.0f;
        float mPauseTimer = 0.0f;
        bool toEnd = true;
        bool startSwing = false;
        bool forwardSwing = true;
};


#endif /* SecurityCamera_hpp */
