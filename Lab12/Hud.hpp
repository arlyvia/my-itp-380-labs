//
//  Hud.hpp
//  Lab12
//
//  Created by Arlyvia Chaialee on 4/29/20.
//

#ifndef Hud_hpp
#define Hud_hpp

#include <stdio.h>
#include "UIComponent.h"
#include "Font.h"

class Hud : public UIComponent {
public:
    Hud(class Actor* owner);
    
    ~Hud();
    
    void Update(float deltaTime) override;
    void Draw(class Shader* shader) override;
    
    Font* mFont;
    
    class Texture* mTimerText;
    class Texture* mCoinText;
    
    class Texture* mCheckpointText;
    
    void UpdateTextTexture(std::string text);
    
    //radar
    class Texture* RadarText;
    class Texture* RadarArrowText;
    class Texture* BlipText;
    
    Vector2 blipHelper(Vector3 player_world_pos, Vector3 other_world_pos);
    Matrix3 mRotMatrix;
    
    Vector2 radar_pos = Vector2(400.0f, -250.0f);
    
    float blip_rotate(Vector3 object_facing);
};

#endif /* Hud_hpp */
