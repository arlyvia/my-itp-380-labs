//
//  HeightMap.hpp
//  Lab08
//
//  Created by Arlyvia Chaialee on 3/25/20.
//

#ifndef HeightMap_hpp
#define HeightMap_hpp

#include <stdio.h>
#include <vector>
#include "Math.h"

class HeightMap
{
public:
    HeightMap(class Game* game);
    
    std::vector<std::vector<int>> mGrid;
    
    float cell_size = 40.55f;
    float grid_top = 1280.0f;
    float grid_left = -1641.0f;
    
    Vector3 CellToWorld(int row, int col);
    
    Vector2 WorldToCell(int x, int y);
    
    bool IsOnTrack(int x, int y);
    
    int GetHeight(int x, int y);
    
private:
    bool IsCellOnTrack(int row, int col);
    float GetHeightFromCell(int row, int col);
    
};

#endif /* HeightMap_hpp */
