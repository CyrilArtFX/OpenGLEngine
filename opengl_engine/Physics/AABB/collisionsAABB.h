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

	static bool IntersectRaycast(const BoxAABBColComp& boxAABB, const Ray& raycast, RaycastHitInfos& outHitInfos);

	static bool IntersectBoxAABB(const BoxAABBColComp& boxAABB, const BoxAABBColComp& otherBoxAABB);


	static bool CollideBodyBox(const RigidbodyComponent& bodyAABB, CollisionResponse& outBodyResponse, const BoxAABBColComp& boxAABB);

	static bool CollideBodies(const RigidbodyComponent& bodyAABBa, CollisionResponse& outBodyAResponse, const RigidbodyComponent& bodyAABBb, CollisionResponse& outBodyBResponse);


private:
	static bool BoxRayIntersection(const Box& box, const Ray& ray, float& distance);

	static bool CCDBoxIntersection(const Box& boxCCD, const Vector3& ccdLastFramePos, const Box& box, float& distance);

	//static bool CCDsIntersection();
};

