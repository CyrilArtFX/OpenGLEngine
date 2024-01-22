#include "collisionComponent.h"
#include "physics.h"

CollisionComponent::~CollisionComponent()
{
	if (registered)
	{
		Physics::RemoveCollision(this);
	}
}

void CollisionComponent::setAssociatedTransform(const Transform* newTransform)
{
	associatedTransform = newTransform;
}

CollisionComponent::CollisionComponent(CollisionType collisionType_, const Transform* associatedTransform_) :
	collisionType(collisionType_), associatedTransform(associatedTransform_)
{
}
