#pragma once
#include "boxAABBColComp.h"
#include <Physics/rigidbodyComponent.h>

/** Collisions AABB
* Static functions that will check collisions that involves AABB components.
*/
class CollisionsAABB
{
public:
	static bool IntersectPoint(const BoxAABBColComp& boxAABB, const Vector3& point);

	static bool IntersectLineRaycast(const BoxAABBColComp& boxAABB, const Ray& raycast, RaycastHitInfos& outHitInfos);

	static bool IntersectAABBRaycast(const BoxAABBColComp& boxAABB, const Box& raycast);

	static bool IntersectBoxAABB(const BoxAABBColComp& boxAABB, const BoxAABBColComp& otherBoxAABB);


	static bool CollideBodyBox(const RigidbodyComponent& bodyAABB, CollisionResponse& outBodyResponse, const BoxAABBColComp& boxAABB);

	static bool CollideBodies(const RigidbodyComponent& bodyAABBa, const RigidbodyComponent& bodyAABBb);


private:
	static bool BoxesIntersection(const Box& boxA, const Box& boxB);

	static bool BoxPointIntersection(const Box& box, const Vector3& point);

	static bool BoxRayIntersection(const Box& box, const Ray& ray, float& distance, Vector3& location, bool computeCollision = false);

	static bool CCDBoxIntersection(const Box& boxCCD, const Vector3& ccdNextFramePos, const Box& box, float& distance, Vector3& location);

	static bool CCDsIntersection(const Box& boxACCD, const Vector3& ccdAMovement, const Box& boxBCCD, const Vector3& ccdBMovement);
};

