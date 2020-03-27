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
    
    //void Update(float deltaTime) override;
    std::vector<Vector3> route_points;
};

#endif /* EnemyMove_hpp */
