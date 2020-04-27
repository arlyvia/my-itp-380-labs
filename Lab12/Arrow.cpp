//
//  Arrow.cpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#include "Arrow.hpp"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Player.hpp"
#include "Actor.h"
#include "Checkpoint.hpp"

Arrow::Arrow(class Game* game, class Actor* parent)
:Actor(game, parent)
{
    arrow_mc = new MeshComponent(this);
    arrow_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Arrow.gpmesh"));
    SetScale(0.15f);
}

void Arrow::OnUpdate(float deltaTime){

    if(GetGame()->mCheckpoints.empty()){
        arrow_q = Quaternion::Identity;
        SetQuaternion(arrow_q);
        return;
    }
    
    Vector3 result = GetGame()->mCheckpoints.front()->GetPosition() - GetGame()->mPlayer->GetPosition();
    
    result.Normalize();
    
    Vector3 unit = Vector3(1.0f,0,0);
    
    float theta = Math::Acos(Vector3::Dot(unit, result));
    
    float check = Vector3::Dot(unit, result);
    
    if (check == 1){
        arrow_q = Quaternion::Identity;
    } else if (check == -1){
        arrow_q = Quaternion(Vector3::UnitZ, theta);
    } else {
        
        Vector3 cross = Vector3::Cross(unit, result);
        
        Vector3 axis = Vector3(cross.x / cross.Length(),
            cross.y / cross.Length(),
            cross.z / cross.Length());
        
        arrow_q = Quaternion(axis, theta);
        
    }
    SetQuaternion(arrow_q);
    SetPosition(GetGame()->GetRenderer()->Unproject(Vector3(0, 250.0f, 0.1f)));
    
}
