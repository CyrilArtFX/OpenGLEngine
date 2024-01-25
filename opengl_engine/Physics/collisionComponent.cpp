#include "collisionComponent.h"
#include "physics.h"
#include <Rendering/material.h>
#include <Utils/color.h>

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

bool CollisionComponent::resolvePoint(const Vector3& point) const
{
	bool intersect = resolvePointIntersection(point);
	intersectedLastFrame = (intersectedLastFrame || intersect);
	return intersect;
}

bool CollisionComponent::resolveRaycast(const Ray& raycast, RaycastHitInfos& outHitInfos) const
{
	bool intersect = resolveRaycastIntersection(raycast, outHitInfos);
	intersectedLastFrame = (intersectedLastFrame || intersect);
	return intersect;
}

bool CollisionComponent::resolveCollision(const CollisionComponent& otherCol) const
{
	bool intersect = resolveCollisionIntersection(otherCol);
	intersectedLastFrame = (intersectedLastFrame || intersect);
	return intersect;
}

void CollisionComponent::drawDebug(Material& debugMaterial) const
{
	debugMaterial.getShader().setVec3("color", intersectedLastFrame ? Color::red : Color::green);
	drawDebugMesh(debugMaterial);
}

const Matrix4 CollisionComponent::getModelMatrix() const
{
	if (!associatedTransform) return Matrix4::identity;

	return associatedTransform->getModelMatrixConst();
}

void CollisionComponent::resetIntersected()
{
	intersectedLastFrame = false;
}

void CollisionComponent::forceIntersected() const
{
	intersectedLastFrame = true;
}

CollisionComponent::CollisionComponent(CollisionType collisionType_, const Transform* associatedTransform_, Mesh* debugMesh_) :
	collisionType(collisionType_), associatedTransform(associatedTransform_), debugMesh(debugMesh_)
{
}
