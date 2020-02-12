#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>
#include <vector>

Actor::Actor(Game* game)
    :mGame(game)
    ,mState(ActorState::Active)
    ,mPosition(Vector2::Zero)
    ,mScale(1.0f)
    ,mRotation(0.0f)
{
    // TODO
    mGame->AddActor(this);
}

Actor::~Actor()
{
    // TODO
    mGame->RemoveActor(this);
    for(auto& component : mComponents)
    {
        delete component;
    }
    mComponents.clear();
}

void Actor::Update(float deltaTime)
{
    // TODO
    if(this->GetState() == ActorState::Active){
        for(int i = 0; i < int(mComponents.size()); i++){
            mComponents[i]->Update(deltaTime);
        }
        OnUpdate(deltaTime);
    }
}

void Actor::OnUpdate(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
    // TODO
    if(this->GetState() == ActorState::Active){
        for(int i = 0; i < int(mComponents.size()); i++){
            mComponents[i]->ProcessInput(keyState);
        }
        OnProcessInput(keyState);
    }
}

void Actor::OnProcessInput(const Uint8* keyState)
{
}

void Actor::AddComponent(Component* c)
{
    mComponents.emplace_back(c);
    std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
        return a->GetUpdateOrder() < b->GetUpdateOrder();
    });
}

Vector2 Actor::GetForward() {
    float theta = this->GetRotation();
    float x_comp = Math::Cos(theta);
    float y_comp = -Math::Sin(theta);
    Vector2 forward = Vector2(x_comp, y_comp);
    return forward;
}
