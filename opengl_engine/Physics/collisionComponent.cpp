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

const Matrix4 CollisionComponent::getModelMatrix() const
{
	if (!associatedTransform) return Matrix4::identity;

	return associatedTransform->getModelMatrixConst();
}

CollisionComponent::CollisionComponent(CollisionType collisionType_, const Transform* associatedTransform_, Mesh* debugMesh_) :
	collisionType(collisionType_), associatedTransform(associatedTransform_), debugMesh(debugMesh_)
{
}
