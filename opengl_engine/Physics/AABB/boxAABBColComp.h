#pragma once
#include <Physics/collisionComponent.h>
#include <Maths/Geometry/box.h>

class RigidbodyComponent;
struct CollisionResponse;


/** Box AABB Collision Component
* Class for collision components of type Box AABB
* This type of collision support position and scale from transform, but not rotation.
*/
class BoxAABBColComp : public CollisionComponent
{
public:
	BoxAABBColComp();
	BoxAABBColComp(const Box& boxValues, Object* objectToAssociate, bool loadPersistent, std::string collisionChannel, CollisionType collisionType = CollisionType::Solid, bool scaleBoxSizeWithTransform = true, bool moveBoxCenterWithObjectScale = true);

	void changeBox(const Box& boxValues);

	const Matrix4 getModelMatrix() const override;

	Vector3 getCenterDownPos() const override;
	Box getEncapsulatingBox() const override;

	Box getTransformedBox(bool forDrawDebug = false) const;

	/** 
	* Get the normal of the surface the given point is on.
	* If the given point isn't on a surface, return Vector3::zero
	*/
	Vector3 getNormal(const Vector3& point) const;

protected:
	bool resolvePointIntersection(const Vector3& point) const override;
	bool resolveLineRaycastIntersection(const Ray& raycast, RaycastHitInfos& outHitInfos) const override;
	bool resolveAABBRaycastIntersection(const Box& raycast) const override;
	bool resolveAABBSweepRaycastIntersection(const Ray& raycast, const Box& boxRaycast, RaycastHitInfos& outHitInfos) const override;

	void drawDebugMesh(Material& debugMaterial) const override;

private:
	Box box{ Box::zero };
	bool useTransformScaleForBoxSize{ true };
	bool useTransformScaleForBoxCenter{ true };
};
