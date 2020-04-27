#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>
#include <vector>
#include <iostream>

Actor::Actor(Game* game, Actor* parent)
    :mGame(game)
    ,mState(ActorState::Active)
    ,mPosition(Vector3::Zero)
    ,mScale(1.0f)
    ,mRotation(0.0f)
{
    // TODO
    mParent = parent;
    if(!mParent) {
        mGame->AddActor(this);
    } else {
        mParent->AddChild(this);
    }
   
}

Actor::~Actor()
{
    // TODO
    //deleting children
    while (!mChildren.empty())
    {
        delete mChildren.back();
    }
    
    for(auto& component : mComponents)
    {
        delete component;
    }
    mComponents.clear();
    
    if(!mParent){
        mGame->RemoveActor(this);
    } else {
        mParent->RemoveChild(this);
    }
}

void Actor::Update(float deltaTime)
{
    // TODO
    CalcWorldTransform();
    
    if(this->GetState() == ActorState::Active){
        for(int i = 0; i < int(mComponents.size()); i++){
            mComponents[i]->Update(deltaTime);
        }
        OnUpdate(deltaTime);
    }
    
    CalcWorldTransform();
    
    for(int unsigned i=0; i < mChildren.size(); i++){
        mChildren[i]->Update(deltaTime);
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

Vector3 Actor::GetForward() {
    float theta = this->GetRotation();
    float x_comp = Math::Cos(theta);
    float y_comp = Math::Sin(theta);
    float z_comp = 0.0f;
    Vector3 forward = Vector3(x_comp, y_comp, z_comp);
    return forward;
}

Vector3 Actor::GetRight() {
    float theta = this->GetRotation();
    float x_comp = Math::Cos(theta + Math::PiOver2);
    float y_comp = Math::Sin(theta + Math::PiOver2);
    float z_comp = 0.0f;
    Vector3 right = Vector3(x_comp, y_comp, z_comp);
    return right;
}

Vector3 Actor::GetQuatForward(){
    Vector3 result = Vector3::Transform(Vector3::UnitX, mQuaternion);
    result.Normalize();
    return result;
}

void Actor::CalcWorldTransform(){
    mScaleMatrix = Matrix4::CreateScale(mScale);
    mRotationMatrix = Matrix4::CreateRotationZ(mRotation);
    mQMatrix = Matrix4::CreateFromQuaternion(mQuaternion);
    mPositionMatrix = Matrix4::CreateTranslation(mPosition);
    
    mWorldTransform = mScaleMatrix * mRotationMatrix * mQMatrix * mPositionMatrix;
    
    if(mParent){
        if(mInheritScale){
            mWorldTransform *= mParent->mWorldTransform;
        } else {
            mWorldTransform *= mParent->CalcWorldRotTrans();
        }
    }
    
}

Matrix4 Actor::CalcWorldRotTrans(){
    Matrix4 RotationMatrix = Matrix4::CreateRotationZ(mRotation);
    Matrix4 QMatrix = Matrix4::CreateFromQuaternion(mQuaternion);
    Matrix4 PositionMatrix = Matrix4::CreateTranslation(mPosition);
    
    Matrix4 WorldTransform = RotationMatrix * QMatrix * PositionMatrix;
    
    if(mParent){
        WorldTransform *= mParent->CalcWorldRotTrans();
    }
    
    return WorldTransform;
}

Vector3 Actor::GetWorldPosition(){
    return mWorldTransform.GetTranslation();
}

Vector3 Actor::GetWorldForward(){
    return mWorldTransform.GetXAxis();
}

void Actor::AddChild(Actor* child){
    mChildren.push_back(child);
}

void Actor::RemoveChild(Actor* child){
    auto iter = std::find(mChildren.begin(), mChildren.end(), child);
    if (iter != mChildren.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        auto iter2 = mChildren.end() - 1;
        std::iter_swap(iter, iter2);
        mChildren.pop_back();
    }
}
