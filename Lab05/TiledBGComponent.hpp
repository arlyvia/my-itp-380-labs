//
//  TiledBGComponent.hpp
//  itp380labs
//
//  Created by Arlyvia Chaialee on 2/26/20.
//

#ifndef TiledBGComponent_hpp
#define TiledBGComponent_hpp

#include <stdio.h>
#include "SpriteComponent.h"
#include <vector>

class TiledBGComponent : public SpriteComponent
{
    public:
        // (Lower draw order corresponds with further back)
        TiledBGComponent(class Actor* owner, int drawOrder = 50);
        //~TiledBGComponent();
    
        void Draw(SDL_Renderer* renderer) override;
    
        std::vector<std::vector<std::string>> csv_storage;
    
        void LoadTileCSV(const std::string& fileName, int tileWidth, int tileHeight);
    
        int mCount = 0;

    protected:
        // Draw order
        int mDrawOrder;
        int mTileWidth;
        int mTileHeight;
};

#endif /* TiledBGComponent_hpp */
