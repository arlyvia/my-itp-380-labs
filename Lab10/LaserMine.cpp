//
//  LaserMine.cpp
//  Lab10
//
//  Created by Arlyvia Chaialee on 4/15/20.
//

#include "LaserMine.hpp"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "LaserComponent.hpp"
#include <iostream>

LaserMine::LaserMine(class Game* game)
:Actor(game)
{
    laserMine_mc = new MeshComponent(this);
    laserMine_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/LaserMine.gpmesh"));
    
    laser_lc = new LaserComponent(this);
    std::cout << "x laser" << GetPosition().x << std::endl;
}
