#pragma once
#include "boxAABBColComp.h"

/** Collisions AABB
* Static functions that will check collisions that involves AABB components.
*/
class CollisionsAABB
{
public:
	static bool IntersectPoint(const BoxAABBColComp& boxAABB, const Vector3& point);

	static bool IntersectRaycast(const BoxAABBColComp& boxAABB, const Ray& raycast, RaycastHitInfos& outHitInfos);

	static bool IntersectBoxAABB(const BoxAABBColComp& boxAABB, const BoxAABBColComp& otherBoxAABB);

	static bool IntersectBoxAABBwithCCD(const BoxAABBColComp& boxAABBwithCCD, const BoxAABBColComp& otherBoxAABB);


private:
	static bool BoxRayIntersection(const Box& box, const Ray& ray, float& distance);
};

