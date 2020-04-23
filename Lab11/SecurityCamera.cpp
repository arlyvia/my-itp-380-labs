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
}
