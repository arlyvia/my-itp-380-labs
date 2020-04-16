//
//  LaserComponent.hpp
//  Lab10
//
//  Created by Arlyvia Chaialee on 4/15/20.
//

#ifndef LaserComponent_hpp
#define LaserComponent_hpp

#include <stdio.h>
#include "MeshComponent.h"
#include "SegmentCast.h"

class LaserComponent: public MeshComponent {
    public:
        //constructor
        LaserComponent(class Actor *owner);
        
        void Update(float deltaTime) override;
        void Draw(class Shader* shader) override;
    
        LineSegment mLineSegment;
    
        Matrix4 worldTransform(LineSegment lineSegment);
};

#endif /* LaserComponent_hpp */
