#pragma once
#include <vector>
#include <SDL2/SDL_stdinc.h>
#include "Math.h"
#include "CollisionComponent.h"

enum class ActorState
{
    Active,
    Paused,
    Destroy
};

class Actor
{
public:
    Actor(class Game* game, Actor* parent);
    virtual ~Actor();

    // Update function called from Game (not overridable)
    void Update(float deltaTime);
    // ProcessInput function called from Game (not overridable)
    void ProcessInput(const Uint8* keyState);

    // Getters/setters
    const Vector3& GetPosition() const { return mPosition; }
    void SetPosition(const Vector3& pos) { mPosition = pos; }
    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }
    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }
    
    ActorState GetState() const { return mState; }
    void SetState(ActorState state) { mState = state; }

    class Game* GetGame() { return mGame; }
    
    // Adds component to Actor (this is automatically called
    // in the component constructor)
    void AddComponent(class Component* c);
    
    //TO-DO
    Vector3 GetForward();
    
    // Returns component of type T, or null if doesn't exist
    template <typename T>
    T* GetComponent() const
    {
        for (auto c : mComponents)
        {
            T* t = dynamic_cast<T*>(c);
            if (t != nullptr)
            {
                return t;
            }
        }
        
        return nullptr;
    }
    
    //matrix
    Matrix4 mWorldTransform;
    const Matrix4& GetWorldTransform() const { return mWorldTransform; }
    
    Matrix4 mScaleMatrix;
    Matrix4 mRotationMatrix;
    Matrix4 mQMatrix;
    Matrix4 mPositionMatrix;
    
    Vector3 GetRight();
    
    //Quaternion
    Quaternion mQuaternion;
    Quaternion GetQuaternion() { return mQuaternion; }
    void SetQuaternion(Quaternion q) { mQuaternion = q; }
    
    Vector3 GetQuatForward();
    
    //actor parenting
    void CalcWorldTransform();
    Matrix4 CalcWorldRotTrans();
    
    Vector3 GetWorldPosition();
    Vector3 GetWorldForward();
    
    Actor* mParent;
    std::vector<Actor*> mChildren;
    bool mInheritScale = false;
    
    void AddChild(Actor* child);
    void RemoveChild(Actor* child);
    
protected:
    // Any actor-specific update code (overridable)
    virtual void OnUpdate(float deltaTime);
    // Any actor-specific update code (overridable)
    virtual void OnProcessInput(const Uint8* keyState);
    
    class Game* mGame;
    // Actor's state
    ActorState mState;

    // Transform
    Vector3 mPosition;
    float mScale;
    float mRotation;
    
    // Components
    std::vector<class Component*> mComponents;
};
