//
//  Hud.cpp
//  Lab12
//
//  Created by Arlyvia Chaialee on 4/29/20.
//

#include "Hud.hpp"
#include "UIComponent.h"
#include "Font.h"
#include "Texture.h"
#include <SDL2/SDL_ttf.h>

Hud::Hud(class Actor* owner)
:UIComponent(owner)
{
    mFont = new Font;
    mFont->Load("Assets/Inconsolata-Regular.ttf");
    
    mTimerText = mFont->RenderText("00:00.00");
}

Hud::~Hud(){
    mFont->Unload();
    delete mFont;
}

void Hud::Update(float deltaTime){
    //mTime += deltaTime;
    //mTimerText->Unload();
    //delete mTimerText;
}

void Hud::Draw(class Shader* shader){
    DrawTexture(shader, mTimerText, Vector2(-420.0f, -325.0f));
    //DrawTexture(shader, mCoinCounter, Vector2(-420.0f, -225.0f));
}


