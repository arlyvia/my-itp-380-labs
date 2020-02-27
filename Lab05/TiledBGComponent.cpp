//
//  TiledBGComponent.cpp
//  itp380labs
//
//  Created by Arlyvia Chaialee on 2/26/20.
//

#include "TiledBGComponent.hpp"
#include "CSVHelper.h"
#include <vector>
#include "Actor.h"
#include "Game.h"

TiledBGComponent::TiledBGComponent(Actor* owner, int drawOrder)
    :SpriteComponent(owner)
    ,mDrawOrder(drawOrder)
{
   
}

void TiledBGComponent::Draw(SDL_Renderer* renderer)
{
    if (mTexture)
    {
        SDL_Rect dest;
        SDL_Rect src;
        int magic_num = GetTexWidth()/mTileWidth;
        for(int i=0; i < 33; i++){
            for(int j=0; j < 48; j++){
                if(std::stoi(csv_storage[i][j]) == -1) continue;
                int row = std::stoi(csv_storage[i][j]) / magic_num;
                int col = std::stoi(csv_storage[i][j]) % magic_num;
                src.w = mTileWidth;
                src.h = mTileHeight;
                src.x = col * mTileWidth;
                src.y = row * mTileHeight;
                
                dest.w = mTileWidth;
                dest.h = mTileHeight;
                dest.x = j * mTileWidth - (int)mOwner->GetGame()->camera_pos.x;
                dest.y = i * mTileHeight - (int)mOwner->GetGame()->camera_pos.y;
                
                SDL_RenderCopyEx(renderer,
                mTexture,
                &src,
                &dest,
                0.0,
                nullptr,
                SDL_FLIP_NONE);
            }
        }
        
        // Draw (have to convert angle from radians to degrees, and clockwise to counter)
        
    }
}

void TiledBGComponent::LoadTileCSV(const std::string& fileName, int tileWidth, int tileHeight){
    std::ifstream textFile;
    textFile.open(fileName);
    if (!textFile) {
        exit(1);
    }
    std::string str = "";
    
    while(textFile){
        std::getline(textFile, str);
        if(str != ""){
            std::vector line = CSVHelper::Split(str);
            csv_storage.push_back(line);
        }
    }
    
    mTileWidth = 32;
    mTileHeight = 32;
    
    /*for(int i=0; i < 33; i++){
        std::cout << std::endl;
        for(int j=0; j < 48; j++){
            std::cout << csv_storage[i][j] << " ";
        }
    }*/
    

}
