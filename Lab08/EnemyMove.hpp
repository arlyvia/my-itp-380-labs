//
//  EnemyMove.hpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/26/20.
//

#ifndef EnemyMove_hpp
#define EnemyMove_hpp

#include <stdio.h>
#include <vector>
#include "VehicleMove.hpp"

class EnemyMove : public VehicleMove
{
public:
    EnemyMove(class Actor* owner);
    
    void Update(float deltaTime) override;
    std::vector<Vector3> route_points;
    
    int currentTarget = 1;
    float mForwardSpeed = 0.0f;
    float mAngularSpeed = 0.0f;
    Vector3 mTarget = Vector3(0,0,0);
};

#endif /* EnemyMove_hpp */
