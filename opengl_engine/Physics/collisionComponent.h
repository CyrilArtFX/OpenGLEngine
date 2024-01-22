#pragma once
#include <Objects/transform.h>
#include "raycast.h"


enum class CollisionType : uint8_t
{
	Null = 0,
	BoxAABB = 1
};


/** Collision Component
* Base class for every collision component
*/
class CollisionComponent
{
public:
	virtual ~CollisionComponent();

	inline CollisionType getCollisionType() const { return collisionType; }

	void setAssociatedTransform(const Transform* newTransform);

	virtual bool resolvePoint(const Vector3& point) const = 0;
	virtual bool resolveRaycast(const Ray& raycast, RaycastHitInfos& outHitInfos) const = 0;
	virtual bool resolveCollision(const CollisionComponent& otherCol) const = 0;

protected:
	CollisionComponent(CollisionType collisionType_, const Transform* associatedTransform_);

	CollisionType collisionType{ CollisionType::Null };
	const Transform* associatedTransform{ nullptr };


	//  for physics manager
public:
	bool registered{ false };
};