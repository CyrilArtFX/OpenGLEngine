#include "collisionsAABB.h"

bool CollisionsAABB::IntersectPoint(const BoxAABBColComp& BoxAABB, const Vector3& point)
{
	return false;
}

bool CollisionsAABB::IntersectRaycast(const BoxAABBColComp& BoxAABB, const Ray& raycast, RaycastHitInfos& outHitInfos)
{
	return false;
}

bool CollisionsAABB::IntersectBoxAABB(const BoxAABBColComp& BoxAABB, const BoxAABBColComp& otherBoxAABB)
{
	return false;
}
