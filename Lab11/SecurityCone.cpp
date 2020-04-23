//
//  SecurityCone.cpp
//  Lab11
//
//  Created by Arlyvia Chaialee on 4/22/20.
//

#include "SecurityCone.hpp"
#include "Actor.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Renderer.h"
#include "Game.h"

SecurityCone::SecurityCone(class Game* game, class Actor* parent)
:Actor(game, parent)
{
    securityCone_mc = new MeshComponent(this, true);
    securityCone_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Cone.gpmesh"));
    
    securityCone_cc = new CollisionComponent(this);
    
    SetPosition(Vector3(30.0f, 0.0f, 0.0f));
    SetScale(3.0f);

}
