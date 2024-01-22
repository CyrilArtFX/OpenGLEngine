#pragma once
#include <Physics/collisionComponent.h>
#include <Maths/Geometry/box.h>


/** Box AABB Collision Component
* Class for collision components of type Box AABB
* This type of collision support position and scale from transform, but not rotation.
*/
class BoxAABBColComp : public CollisionComponent
{
public:
	BoxAABBColComp();
	BoxAABBColComp(Box boxValues, const Transform* transformToAssociate, bool scaleBoxSizeWithTransform = true);

	bool resolvePoint(const Vector3& point) const override;
	bool resolveRaycast(const Ray& raycast, RaycastHitInfos& outHitInfos) const override;
	bool resolveCollision(const CollisionComponent& otherCol) const override;

	Box getTransformedBox() const;

private:
	Box box{ Box::zero };
	bool useTransformScaleForBoxSize{ true };
};
