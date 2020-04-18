//
//  VehicleMove.cpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/24/20.
//

#include "VehicleMove.hpp"
#include "Actor.h"
#include "Game.h"
#include "HeightMap.hpp"
#include "CSVHelper.h"
#include <iostream>
#include <fstream>
#include <vector>

VehicleMove::VehicleMove(class Actor* owner)
:Component(owner, 50)
{
   std::ifstream textFile;
   textFile.open("Assets/HeightMap/Checkpoints.csv");
   if (!textFile) {
       exit(1);
   }
   std::string str = "";
   
    std::getline(textFile,str);
    //int i = 0;
   while(textFile){
       std::getline(textFile, str);
       std::vector line = CSVHelper::Split(str);
       if (line[0] == "Checkpoint"){
           for(int i = 0; i < 4; i++){
               four_checkpoint.push_back(std::stoi(line[i+1]));
           }
           all_checkpoints.push_back(four_checkpoint);
       }
    }
    
}

VehicleMove::~VehicleMove(){}

void VehicleMove::Update(float deltaTime)
{
    mDriveTimer = mDriveTimer + deltaTime;
    
    float lerp = mDriveTimer/accelRampTime;
    
    if(mPressed){
        if (lerp > 1.0) lerp = 1.0f;
        float accelerationMagnitude = Math::Lerp(minLinAccelMag, maxLinAccelMag, lerp);
        mVelocity = mVelocity + mOwner->GetForward() * accelerationMagnitude * deltaTime;
    } else {
        mDriveTimer = 0.0f;
    }
    
    mOwner->SetPosition(mOwner->GetPosition() + mVelocity * deltaTime);
    
    int z_pos = Math::Lerp(mOwner->GetPosition().z, mOwner->GetGame()->mHeightMap->GetHeight(mOwner->GetPosition().x,
                                                                                              mOwner->GetPosition().y), 0.1f);
    
    if(mOwner->GetGame()->mHeightMap->IsOnTrack(mOwner->GetPosition().x, mOwner->GetPosition().y)){
        mOwner->SetPosition(Vector3(mOwner->GetPosition().x, mOwner->GetPosition().y, z_pos));
    }
       //bool HeightMap::IsOnTrack(float x, float y){
    
    if(mPressed){
       mVelocity = mVelocity * linDragCoeffPressed;
   } else {
       mVelocity = mVelocity * linDragCoeff;
   }
    
    if(mTurn == Turn::Left){
        mAngularVelocity = mAngularVelocity + angularAccel * -1.0f * deltaTime;
    } else if(mTurn == Turn::Right){
        mAngularVelocity = mAngularVelocity + angularAccel * 1.0f * deltaTime;
    }
    
    //angularAccel = angularAccel + mAngularVelocity * deltaTime;
    
    mAngularVelocity = mAngularVelocity * angularDragCoeff;
    mOwner->SetRotation(mOwner->GetRotation() + mAngularVelocity * deltaTime);
    
    /*for(int i = 0; i < all_checkpoints.size(); i++){
        for(int j = 0; j < 4; j++){
            std::cout << "all" << all_checkpoints[i][j] <<std::endl;
        }
    }*/
   
    Vector2 playerPos = mOwner->GetGame()->mHeightMap->WorldToCell(mOwner->GetPosition().x, mOwner->GetPosition().y);
    int next_checkpoint;
    
    if(last_checkpoint < 8){
        next_checkpoint = last_checkpoint+1;
    } else if(last_checkpoint == 8) {
        next_checkpoint = 0;
    }
    
    int int_playerPosX = (int)playerPos.x;
    int int_playerPosY = (int)playerPos.y;
    
    //std::cout<< "next" << next_checkpoint <<std::endl;
    if(int_playerPosX >= all_checkpoints[next_checkpoint][0]
       && int_playerPosX <= all_checkpoints[next_checkpoint][1]
       && int_playerPosY >= all_checkpoints[next_checkpoint][2]
       && int_playerPosY <= all_checkpoints[next_checkpoint][3]){
        
        if(last_checkpoint == 8){
            last_checkpoint = 0;
        } else {
            last_checkpoint++;
        }
        if(last_checkpoint == 0){
            current_lap++;
            OnLapChange(current_lap);
        }
    }
    
    std::cout << "lap: " << current_lap << std::endl;
    std::cout << "checkpoint: " << last_checkpoint << std::endl;
}
