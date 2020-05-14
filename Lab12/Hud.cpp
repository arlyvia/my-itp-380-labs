//
//  Hud.cpp
//  Lab12
//
//  Created by Arlyvia Chaialee on 4/29/20.
//

#include "Hud.hpp"
#include "UIComponent.h"
#include "Font.h"
#include "Player.hpp"
#include "SecurityCamera.hpp"
#include "Actor.h"
#include "Texture.h"
#include "Actor.h"
#include "Renderer.h"
#include "Game.h"
#include "Checkpoint.hpp"
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
    
    RadarText = mOwner->GetGame()->GetRenderer()->GetTexture("Assets/Radar.png");
    RadarArrowText = mOwner->GetGame()->GetRenderer()->GetTexture("Assets/RadarArrow.png");
    BlipText = mOwner->GetGame()->GetRenderer()->GetTexture("Assets/Blip.png");
}

Hud::~Hud(){
    mFont->Unload();
    delete mFont;
}

void Hud::Update(float deltaTime){
    mOwner->GetGame()->mTime += deltaTime;
    
    mOwner->GetGame()->mCheckpointTimer += deltaTime;
    
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
    DrawTexture(shader, mCheckpointText, Vector2::Zero);
    DrawTexture(shader, RadarText, Vector2(radar_pos));
    DrawTexture(shader, RadarArrowText, Vector2(radar_pos));
    
    for(int unsigned i=0; i < mOwner->GetGame()->mSecurityCameras.size(); i++){
        Vector2 blip_pos = blipHelper(mOwner->GetGame()->mPlayer->GetWorldPosition(), mOwner->GetGame()->mSecurityCameras[i]->GetWorldPosition());
        float blip_angle = blip_rotate(mOwner->GetGame()->mSecurityCameras[i]->GetQuatForward());
        DrawTexture(shader, BlipText, blip_pos, 1.0f, blip_angle);
    }
}

void Hud::UpdateTextTexture(std::string text){
    //std::string checkpointText = mOwner->GetGame()->mCurrCheckpoint->GetCheckpointText();
    std::string checkpointText;
    //std::cout << "timer " << mOwner->GetGame()->mCheckpointTimer << std::endl;
    if(mOwner->GetGame()->mCheckpointTimer > 5.0f && mOwner->GetGame()->at_next_checkpoint){
        checkpointText = "";
        mOwner->GetGame()->mCheckpointTimer = 0.0f;
        mOwner->GetGame()->at_next_checkpoint = true;
        
    } else {
        
        checkpointText = text;
        mOwner->GetGame()->at_next_checkpoint = false;
    }
    checkpointText = text;
    mCheckpointText = mFont->RenderText(checkpointText);
}

Vector2 Hud::blipHelper(Vector3 player_world_pos, Vector3 other_world_pos){
    
    Vector2 final_pos = Vector2(-1000.0f, -1000.0f);
    
    Vector2 player2D = Vector2(player_world_pos.y, player_world_pos.x);
    Vector2 other2D = Vector2(other_world_pos.y, other_world_pos.x);
    
    Vector2 PO = other2D - player2D;
    
    float rotation_angle = Math::Atan2(player2D.x, player2D.y);
    
    mRotMatrix = Matrix3::CreateRotation(rotation_angle);
    
    if(PO.Length() <= 1500.0f){
        PO.x /= 1500.0f;
        PO.y /= 1500.0f;
        
        PO.x *= 92.0f;
        PO.y *= 92.0f;
        
        Vector2 relative_pos = Vector2::Transform(PO, mRotMatrix);
        
        final_pos = radar_pos + relative_pos;
        
    }
    
    return final_pos;
    
}

float Hud::blip_rotate(Vector3 object_facing){
    Vector2 object2D = Vector2(object_facing.y, object_facing.x);
    
    Vector2::Transform(object2D, mRotMatrix);
    
    float angle = Math::Atan2(object2D.y, object2D.x);
    
    return angle;
}

