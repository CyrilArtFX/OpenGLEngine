#include "collisionComponent.h"

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::setAssociatedTransform(const Transform* newTransform)
{
	associatedTransform = newTransform;
}

CollisionComponent::CollisionComponent(CollisionType collisionType_, const Transform* associatedTransform_) :
	collisionType(collisionType_), associatedTransform(associatedTransform_)
{
}
