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
	BoxAABBColComp(const Box& boxValues, Transform* transformToAssociate, bool scaleBoxSizeWithTransform = true);

	const Matrix4 getModelMatrix() const override;

	Box getTransformedBox(bool forDrawDebug = false) const;
	Vector3 getLastFrameTransformedPos() const;

protected:
	bool resolvePointIntersection(const Vector3& point) const override;
	bool resolveRaycastIntersection(const Ray& raycast, RaycastHitInfos& outHitInfos) const override;
	bool resolveCollisionIntersection(const CollisionComponent& otherCol) const override;
	bool resolveRigidbodyIntersection(const RigidbodyComponent& rigidbody, CollisionResponse& outResponse) const override;
	bool resolveRigidbodySelfIntersection(const RigidbodyComponent& rigidbody, CollisionResponse& outResponse, const RigidbodyComponent& selfRigidbody, CollisionResponse& outSelfResponse) const override;

	void drawDebugMesh(Material& debugMaterial) const override;

private:
	Box box{ Box::zero };
	bool useTransformScaleForBoxSize{ true };
};
