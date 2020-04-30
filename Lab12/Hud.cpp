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
#include "Actor.h"
#include "Game.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

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
    mOwner->GetGame()->mTime += deltaTime;
    mTimerText->Unload();
    delete mTimerText;
    
    float minutes = mOwner->GetGame()->mTime / 60.0f;
    int minute = (int)minutes;
    float seconds = fmod(mOwner->GetGame()->mTime, 60.0f);
    float fraction = fmod(mOwner->GetGame()->mTime * 100.0f, 100.0f);
    
    std::stringstream timerText;
    
    char buf[1024];
    sprintf(buf, "%02d:%02d.%02d", minute, (int)seconds, (int)fraction);
    timerText << std::string(buf) << std::endl;
   
    mTimerText = mFont->RenderText(timerText.str());
    
    std::string coinText = std::to_string(mOwner->GetGame()->mCoinCount) + "/55";
    
    mCoinText = mFont->RenderText(coinText);
}

void Hud::Draw(class Shader* shader){
    DrawTexture(shader, mTimerText, Vector2(-420.0f, -325.0f));
    DrawTexture(shader, mCoinText, Vector2(-443.0f, -300.0f));
}


