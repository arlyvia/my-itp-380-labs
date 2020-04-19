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
#include "Player.hpp"
#include "Actor.h"
#include "Math.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

EnemyMove::EnemyMove(class Actor* owner)
:VehicleMove(owner)
{
   std::ifstream textFile;
   textFile.open("Assets/HeightMap/Path.csv");
   if (!textFile) {
       exit(1);
   }
   std::string str = "";
   
    std::getline(textFile,str);
    //std::cout << "str1:" << str << std::endl;
    //int i = 0;
   while(textFile){
       std::getline(textFile, str);
       //std::cout << str << std::endl;
       std::vector line = CSVHelper::Split(str);
       if (line[0] == "Node"){
            Vector3 point = mOwner->GetGame()->mHeightMap->CellToWorld(std::stoi(line[1]), std::stoi(line[2]));
            route_points.push_back(point);
       }
    }
    
    mOwner->SetPosition(route_points[0]);
}

void EnemyMove::Update(float deltaTime){
    Vector3 v;
    v = route_points[currentTarget] - mOwner->GetPosition();
    v.Normalize();
    
    //or 40.0f
    if( (route_points[currentTarget] - mOwner->GetPosition()).Length() < 65.0f){
        currentTarget = currentTarget+1;
        if((unsigned)currentTarget == route_points.size()) currentTarget = 0;
    }
    
    if(Vector3::Dot(mOwner->GetForward(), v) > 0.7f){
        SetPressed(true);
    } else {
        SetPressed(false);
    }
    
    Vector3 turn = Vector3::Cross(mOwner->GetForward(), v);
    if(turn.z > 0){
        SetTurn(Turn::Right);
    } else {
        SetTurn(Turn::Left);
    }

    /*if( (mOwner->GetGame()->mPlayer->GetPosition() - mOwner->GetPosition()).Length() < 100.0f){
        mTarget = mOwner->GetGame()->mPlayer->GetPosition() - mOwner->GetPosition();
    }*/
    
    VehicleMove::Update(deltaTime);
}
