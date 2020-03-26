//
//  HeightMap.cpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/25/20.
//

#include "HeightMap.hpp"
#include "Game.h"
#include "CSVHelper.h"
#include "Math.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

HeightMap::HeightMap(Game* game){
    std::ifstream textFile;
    textFile.open("Assets/HeightMap/HeightMap.csv");
    if (!textFile) {
        exit(1);
    }
    std::string str = "";
    
    while(textFile){
        std::getline(textFile, str);
        if(str != ""){
            std::vector line = CSVHelper::Split(str);
            std::vector<int> temp;
            for(unsigned int i=0; i < line.size(); i++){
                temp.push_back(std::stoi(line[i]));
            }
            mGrid.push_back(temp);
        }
    }
    /*for(int i = 0; (unsigned)i < 64; i++){
        std::cout << std::endl;
        for(int j = 0; j < 64; j++){
            std::cout << mGrid[i][j] << std::endl;
        }
    }*/
}

bool HeightMap::IsCellOnTrack(int row, int col){
    if (row > 64 || col > 64 || row < 0 || col < 0){
        return false;
    } else if (mGrid[row][col] == -1) {
        return false;
    } else {
        return true;
    }
}

float HeightMap::GetHeightFromCell(int row, int col){
    int cellValue = mGrid[row][col];
    std::cout << "cv" << cellValue << std::endl;
    float temp = -40.0f + cellValue * 5.0f;
    return temp;
}

Vector3 HeightMap::CellToWorld(int row, int col){
    if (IsCellOnTrack(row, col)) {
        float x = grid_top - cell_size * row;
        float y = grid_left + cell_size * col;
        float z = GetHeightFromCell(row, col);
       
        return Vector3(x, y, z);
    } else {
        return Vector3::Zero;
    }
}

Vector2 HeightMap::WorldToCell(float x, float y){
    int row = (abs(x-grid_top) + cell_size/2.0f) / cell_size;
    int col = (abs(y-grid_left) + cell_size/2.0f) / cell_size;
    return Vector2(row, col);
}

bool HeightMap::IsOnTrack(float x, float y){
    if(IsCellOnTrack(WorldToCell(x,y).x, WorldToCell(x,y).y)){
        return true;
    } else {
        return false;
    }
}

int HeightMap::GetHeight(float x, float y){
    if(IsCellOnTrack(WorldToCell(x,y).x, WorldToCell(x,y).y)){
       return GetHeightFromCell(WorldToCell(x,y).x, WorldToCell(x,y).y);
    } else{
       return -1000;
    }
}
