#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
,mDepth(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	Vector3 aMin = GetMin();
	Vector3 aMax = GetMax();
	Vector3 bMin = other->GetMin();
	Vector3 bMax = other->GetMax();

	bool no = aMax.x < bMin.x ||
		aMax.y < bMin.y ||
		aMax.z < bMin.z ||
		bMax.x < aMin.x ||
		bMax.y < aMin.y ||
		bMax.z < aMin.z;

	return !no;
}

Vector3 CollisionComponent::GetMin() const
{
	Vector3 v = mOwner->GetPosition();
	v.x -= mDepth * mOwner->GetScale() / 2.0f;
	v.y -= mWidth * mOwner->GetScale() / 2.0f;
	v.z -= mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

Vector3 CollisionComponent::GetMax() const
{
	Vector3 v = mOwner->GetPosition();
	v.x += mDepth * mOwner->GetScale() / 2.0f;
	v.y += mWidth * mOwner->GetScale() / 2.0f;
	v.z += mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

const Vector3& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(
	const CollisionComponent* other, Vector3& offset)
{
	offset = Vector3::Zero;
    // TODO: Implement
    if(!(this->Intersect(other))){
        return CollSide::None;
    } else {
        float otherMinYDiff = other->GetMin().y - this->GetMax().y;
        float otherMaxYDiff = other->GetMax().y - this->GetMin().y;
        float otherMinXDiff = other->GetMin().x - this->GetMax().x;
        float otherMaxXDiff = other->GetMax().x - this->GetMin().x;
        float otherMinZDiff = other->GetMin().z - this->GetMax().z;
        float otherMaxZDiff = other->GetMax().z - this->GetMin().z;
        
        if((Math::Abs(otherMinYDiff) <= Math::Abs(otherMaxYDiff))
            && (Math::Abs(otherMinYDiff) <= Math::Abs(otherMinXDiff))
            && (Math::Abs(otherMinYDiff) <= Math::Abs(otherMaxXDiff))
            && (Math::Abs(otherMinYDiff) <= Math::Abs(otherMinZDiff))
            && (Math::Abs(otherMinYDiff) <= Math::Abs(otherMaxZDiff))){
            offset.y = otherMinYDiff;
            return CollSide::SideMinY;
        } else if((Math::Abs(otherMaxYDiff) <= Math::Abs(otherMinYDiff))
            && (Math::Abs(otherMaxYDiff) <= Math::Abs(otherMinXDiff))
            && (Math::Abs(otherMaxYDiff) <= Math::Abs(otherMaxXDiff))
            && (Math::Abs(otherMaxYDiff) <= Math::Abs(otherMinZDiff))
            && (Math::Abs(otherMaxYDiff) <= Math::Abs(otherMaxZDiff))){
            offset.y = otherMaxYDiff;
            return CollSide::SideMaxY;
        } else if((Math::Abs(otherMinXDiff) <= Math::Abs(otherMinYDiff))
            && (Math::Abs(otherMinXDiff) <= Math::Abs(otherMaxYDiff))
            && (Math::Abs(otherMinXDiff) <= Math::Abs(otherMaxXDiff))
            && (Math::Abs(otherMinXDiff) <= Math::Abs(otherMinZDiff))
            && (Math::Abs(otherMinXDiff) <= Math::Abs(otherMaxZDiff))){
            offset.x = otherMinXDiff;
            return CollSide::SideMinX;
        } else if((Math::Abs(otherMaxXDiff) <= Math::Abs(otherMinYDiff))
            && (Math::Abs(otherMaxXDiff) <= Math::Abs(otherMaxYDiff))
            && (Math::Abs(otherMaxXDiff) <= Math::Abs(otherMinXDiff))
            && (Math::Abs(otherMaxXDiff) <= Math::Abs(otherMinZDiff))
            && (Math::Abs(otherMaxXDiff) <= Math::Abs(otherMaxZDiff))){
            offset.x = otherMaxXDiff;
            return CollSide::SideMaxX;
        } else if((Math::Abs(otherMinZDiff) <= Math::Abs(otherMaxYDiff))
            && (Math::Abs(otherMinZDiff) <= Math::Abs(otherMinXDiff))
            && (Math::Abs(otherMinZDiff) <= Math::Abs(otherMaxXDiff))
            && (Math::Abs(otherMinZDiff) <= Math::Abs(otherMinYDiff))
            && (Math::Abs(otherMinZDiff) <= Math::Abs(otherMaxZDiff))){
            offset.z = otherMinZDiff;
            return CollSide::Bottom;
        } else {
            offset.z = otherMaxZDiff;
            return CollSide::Top;
        }
    }
	// TODO: Implement
	return CollSide::None;
}
