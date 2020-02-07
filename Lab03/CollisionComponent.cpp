#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	// TODO: Implement
    
    if (!(this->GetMax().x < other->GetMin().x)
       && !(other->GetMax().x < this->GetMin().x)
       && !(this->GetMax().y < other->GetMin().y)
       && !(other->GetMax().y < this->GetMin().y)){
        return true;
    } else {
        return false;
    }
}

Vector2 CollisionComponent::GetMin() const
{
	// TODO: Implement
    Vector2 min;
    min.x = this->mOwner->GetPosition().x - (mWidth * this->mOwner->GetScale()) / 2.0f;
    min.y = this->mOwner->GetPosition().y - (mHeight * this->mOwner->GetScale()) / 2.0f;
	return min;
}

Vector2 CollisionComponent::GetMax() const
{
	// TODO: Implement
    Vector2 max;
    max.x = this->mOwner->GetPosition().x + (mWidth * this->mOwner->GetScale()) / 2.0f;
    max.y = this->mOwner->GetPosition().y + (mHeight * this->mOwner->GetScale()) / 2.0f;
    return max;
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(
	const CollisionComponent* other, Vector2& offset)
{
	offset = Vector2::Zero;
	// TODO: Implement
	return CollSide::None;
}
