//
//  SecurityCamera.cpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#include "SecurityCamera.hpp"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "SecurityCone.hpp"
#include "Player.hpp"

SecurityCamera::SecurityCamera(class Game* game, class Actor* parent)
:Actor(game, parent)
{
    securityCamera_mc = new MeshComponent(this);
    securityCamera_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Camera.gpmesh"));
    
    securityCamera_cc = new CollisionComponent(this);
    securityCamera_cc->SetSize(25.0f, 25.0f, 25.0f);
    
    securityCamera_sco = new SecurityCone(game, this);
    
    GetGame()->mSecurityCameras.push_back(this);
}

SecurityCamera::~SecurityCamera()
{
    auto iter = std::find(GetGame()->mSecurityCameras.begin(), GetGame()->mSecurityCameras.end(), this);
    if (iter != GetGame()->mSecurityCameras.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        auto iter2 = GetGame()->mSecurityCameras.end() - 1;
        std::iter_swap(iter, iter2);
        GetGame()->mSecurityCameras.pop_back();
    }
}
