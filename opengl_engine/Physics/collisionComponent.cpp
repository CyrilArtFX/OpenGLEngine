#include "collisionComponent.h"
#include "physics.h"
#include "rigidbodyComponent.h"
#include <Rendering/material.h>
#include <Utils/color.h>

CollisionComponent::~CollisionComponent()
{
	if (registered)
	{
		Physics::RemoveCollision(this);
	}

	onCollisionDelete.broadcast();
}

void CollisionComponent::setAssociatedTransform(Transform* newTransform)
{
	associatedTransform = newTransform;
}

bool CollisionComponent::resolvePoint(const Vector3& point) const
{
	bool intersect = resolvePointIntersection(point);
	//intersectedLastFrame = (intersectedLastFrame || intersect);
	return intersect;
}

bool CollisionComponent::resolveRaycast(const Ray& raycast, RaycastHitInfos& outHitInfos) const
{
	bool intersect = resolveRaycastIntersection(raycast, outHitInfos);
	//  it's up to the physics manager to set the intersected last frame
	//  the physics manager also broadcast the onRaycastIntersect event
	return intersect;
}

bool CollisionComponent::resolveCollision(const CollisionComponent& otherCol) const
{
	bool intersect = resolveCollisionIntersection(otherCol);
	//  it's up to the physics manager to set the intersected last frame (for both collisions)
	//  the physics manager also broadcast the onCollisionIntersect event (for both collisions)
	return intersect;
}

bool CollisionComponent::resolveRigidbody(const RigidbodyComponent& rigidbody, CollisionResponse& outResponse) const
{
	bool intersect = resolveRigidbodyIntersection(rigidbody, outResponse);
	//  it's up to the physics manager to set the intersected last frame (for both collisions)
	//  the physics manager also broadcast the onCollisionIntersect event (for both collisions)
	return intersect;
}

bool CollisionComponent::resolveRigidbodySelf(const RigidbodyComponent& rigidbody, CollisionResponse& outResponse, const RigidbodyComponent& selfRigidbody, CollisionResponse& outSelfResponse) const
{
	bool intersect = resolveRigidbodySelfIntersection(rigidbody, outResponse, selfRigidbody, outSelfResponse);
	//  it's up to the physics manager to set the intersected last frame (for both collisions)
	//  the physics manager also broadcast the onCollisionIntersect event (for both collisions)
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

void CollisionComponent::addPosition(const Vector3& posToAdd)
{
	if (!associatedTransform) return;
	associatedTransform->setPosition(associatedTransform->getPosition() + posToAdd);
}

CollisionComponent::CollisionComponent(CollisionType collisionType_, Transform* associatedTransform_, Mesh* debugMesh_, bool loadPersistent_) :
	PhysicEntity(loadPersistent_),
	collisionType(collisionType_), associatedTransform(associatedTransform_), debugMesh(debugMesh_)
{
}
