#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner)
:Component(owner, 50)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
	// TODO: Implement in Part 2
    mOwner->SetRotation(mOwner->GetRotation() + GetAngularSpeed() * deltaTime);
    
    Vector2 velocity = mOwner->GetForward() * GetForwardSpeed();
    mOwner->SetPosition(mOwner->GetPosition() + velocity * deltaTime);
}
