//
//  Key.cpp
//  Lab05
//
//  Created by Arlyvia Chaialee on 3/2/20.
//

#include "Key.hpp"
#include "Game.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

Key::Key(class Game* game)
:Actor(game)
{
    key_cc = new CollisionComponent(this);
    key_cc->SetSize(16.0f, 32.0f);
    key_sc = new SpriteComponent(this);
    key_sc->SetTexture(GetGame()->GetTexture("Assets/Key.png"));
}
