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
    class Texture* mCoinCounter;
    
    float mTime = 0.0f;
};

#endif /* Hud_hpp */
