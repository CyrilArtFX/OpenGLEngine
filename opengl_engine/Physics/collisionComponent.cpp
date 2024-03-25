#include "collisionComponent.h"
#include "physics.h"
#include "rigidbodyComponent.h"
#include "ObjectChannels/collisionChannels.h"
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

void CollisionComponent::setAssociatedObject(Object* newObject)
{
	associatedObject = newObject;
}

bool CollisionComponent::resolvePoint(const Vector3& point) const
{
	bool intersect = resolvePointIntersection(point);
	return intersect;
}

bool CollisionComponent::resolveLineRaycast(const Ray& raycast, RaycastHitInfos& outHitInfos, const std::vector<std::string> testChannels) const
{
	if (!channelTest(testChannels)) return false;

	bool intersect = resolveLineRaycastIntersection(raycast, outHitInfos);
	//  it's up to the physics manager to broadcast the onRaycastIntersect event
	return intersect;
}

bool CollisionComponent::resolveAABBRaycast(const Box& raycast, const std::vector<std::string> testChannels) const
{
	if (!channelTest(testChannels)) return false;

	bool intersect = resolveAABBRaycastIntersection(raycast);
	//  it's up to the physics manager to broadcast the onRaycastIntersect event
	return intersect;
}

bool CollisionComponent::resolveAABBSweepRaycast(const Ray& raycast, const Box& boxRaycast, RaycastHitInfos& outHitInfos, const std::vector<std::string> testChannels) const
{
	if (!channelTest(testChannels)) return false;

	bool intersect = resolveAABBSweepRaycastIntersection(raycast, boxRaycast, outHitInfos);
	//  it's up to the physics manager to broadcast the onRaycastIntersect event
	return intersect;
}

bool CollisionComponent::resolveCollision(const CollisionComponent& otherCol, const std::vector<std::string> testChannels) const
{
	if (!channelTest(testChannels)) return false;

	bool intersect = resolveCollisionIntersection(otherCol);
	//  it's up to the physics manager to set the intersected last frame (for both collisions)
	//  the physics manager also broadcast the onCollisionIntersect event (for both collisions)
	return intersect;
}

bool CollisionComponent::resolveRigidbody(const RigidbodyComponent& rigidbody, CollisionResponse& outResponse) const
{
	if (!channelTest(rigidbody.getTestChannels())) return false;

	bool intersect = resolveRigidbodyIntersection(rigidbody, outResponse);
	//  it's up to the physics manager to set the intersected last frame (for both collisions)
	//  the physics manager also broadcast the onCollisionIntersect event (for both collisions)
	return intersect;
}

bool CollisionComponent::resolveRigidbodySelf(const RigidbodyComponent& rigidbody, const RigidbodyComponent& selfRigidbody) const
{
	if (!channelTest(rigidbody.getTestChannels()) || !rigidbody.getAssociatedCollision().channelTest(selfRigidbody.getTestChannels())) return false;

	bool intersect = resolveRigidbodySelfIntersection(rigidbody, selfRigidbody);
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
	if (!associatedObject) return Matrix4::identity;

	return associatedObject->getModelMatrixConst();
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
	if (!associatedObject) return;
	associatedObject->setPosition(associatedObject->getPosition() + posToAdd);
}

void CollisionComponent::setCollisionChannel(std::string newCollisionChannel)
{
	collisionChannel = newCollisionChannel;
}

CollisionComponent::CollisionComponent(CollisionType collisionType_, Object* associatedObject_, Mesh* debugMesh_, bool loadPersistent_, std::string collisionChannel_) :
	PhysicEntity(loadPersistent_),
	collisionType(collisionType_), associatedObject(associatedObject_), debugMesh(debugMesh_), collisionChannel(collisionChannel_)
{
}

bool CollisionComponent::channelTest(const std::vector<std::string> testChannels) const
{
	for (auto test_channel : testChannels)
	{
		if (test_channel == "") continue;

		if(test_channel == CollisionChannels::DefaultEverything()) return true;

		if (test_channel == collisionChannel) return true;
	}

	return false;
}
