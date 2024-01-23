#include "collisionsAABB.h"

bool CollisionsAABB::IntersectPoint(const BoxAABBColComp& boxAABB, const Vector3& point)
{
	Box box = boxAABB.getTransformedBox();
	Vector3 box_min = box.getMinPoint();
	Vector3 box_max = box.getMaxPoint();

	return
		point.x >= box_min.x && point.x <= box_max.x &&
		point.y >= box_min.y && point.y <= box_max.y &&
		point.z >= box_min.z && point.z <= box_max.z;
}

bool CollisionsAABB::IntersectRaycast(const BoxAABBColComp& boxAABB, const Ray& raycast, RaycastHitInfos& outHitInfos)
{
	return false;
}

bool CollisionsAABB::IntersectBoxAABB(const BoxAABBColComp& boxAABB, const BoxAABBColComp& otherBoxAABB)
{
	return false;
}
