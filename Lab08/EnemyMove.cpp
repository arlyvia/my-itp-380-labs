//
//  EnemyMove.cpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/26/20.
//

#include "EnemyMove.hpp"
#include "CSVHelper.h"
#include "HeightMap.hpp"
#include "Game.h"
#include "VehicleMove.hpp"
#include "Actor.h"
#include "Math.h"
#include <fstream>
#include <vector>
#include <string>

EnemyMove::EnemyMove(class Actor* owner)
:VehicleMove(owner)
{
   std::ifstream textFile;
   textFile.open("Assets/HeightMap/Path.csv");
   if (!textFile) {
       exit(1);
   }
   std::string str = "";
   
   while(textFile){
       std::getline(textFile, str);
       if(str != ""){
           std::vector line = CSVHelper::Split(str);
            Vector3 point = mOwner->GetGame()->mHeightMap->CellToWorld(std::stoi(temp[1]), std::stoi(temp[2]));
            route_points.push_back(point);
       }

    
    mOwner->SetPosition(route_points[0]);
}

//void EnemyMove::Update(float deltaTime){
    //VehicleMove::Update(deltaTime);
}
