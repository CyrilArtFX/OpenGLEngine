#include "collisionsAABB.h"
#include <Maths/maths.h>

using Maths::max;
using Maths::min;

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
	Box box = boxAABB.getTransformedBox();

	float hit_distance = 0.0f;

	bool intersect = BoxRayIntersection(box, raycast, hit_distance);
	
	//  check if it is the closest collision found
	if (hit_distance < outHitInfos.hitDistance)
	{
		outHitInfos.hitDistance = hit_distance;
		outHitInfos.hitLocation = raycast.getOrigin() + raycast.getDirection() * hit_distance;
		outHitInfos.hitCollision = &boxAABB;
	}

	return intersect;
}

bool CollisionsAABB::IntersectBoxAABB(const BoxAABBColComp& boxAABB, const BoxAABBColComp& otherBoxAABB)
{
	Box box_a = boxAABB.getTransformedBox();
	Vector3 box_a_min = box_a.getMinPoint();
	Vector3 box_a_max = box_a.getMaxPoint();

	Box box_b = otherBoxAABB.getTransformedBox();
	Vector3 box_b_min = box_b.getMinPoint();
	Vector3 box_b_max = box_b.getMaxPoint();


	return box_a_min < box_b_max && box_a_max > box_b_min;
}

bool CollisionsAABB::IntersectBoxAABBwithCCD(const BoxAABBColComp& boxAABBwithCCD, const BoxAABBColComp& otherBoxAABB)
{
	Box box_ccd = boxAABBwithCCD.getTransformedBox();
	Vector3 box_ccd_pos = box_ccd.getCenterPoint();
	Vector3 box_ccd_pos_last_frame = boxAABBwithCCD.getLastFrameTransformedPos();

	Box box_static = otherBoxAABB.getTransformedBox();
	box_static.addHalfExtents(box_ccd);

	Ray ray;
	ray.setupWithStartEnd(box_ccd_pos_last_frame, box_ccd_pos);

	float hit_distance = 0.0f;

	bool intersect = BoxRayIntersection(box_static, ray, hit_distance);

	return intersect;
}


bool CollisionsAABB::BoxRayIntersection(const Box& box, const Ray& ray, float& distance)
{
	Vector3 box_min = box.getMinPoint();
	Vector3 box_max = box.getMaxPoint();

	Vector3 ray_origin = ray.getOrigin();
	Vector3 ray_direction = ray.getDirection();
	float ray_length = ray.getLength();

	Vector3 dirfrac;
	dirfrac.x = 1.0f / ray_direction.x;
	dirfrac.y = 1.0f / ray_direction.y;
	dirfrac.z = 1.0f / ray_direction.z;

	float t1 = (box_min.x - ray_origin.x) * dirfrac.x;
	float t2 = (box_max.x - ray_origin.x) * dirfrac.x;
	float t3 = (box_min.y - ray_origin.y) * dirfrac.y;
	float t4 = (box_max.y - ray_origin.y) * dirfrac.y;
	float t5 = (box_min.z - ray_origin.z) * dirfrac.z;
	float t6 = (box_max.z - ray_origin.z) * dirfrac.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	distance = std::numeric_limits<float>::max();

	//  if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		return false;
	}

	//  if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return false;
	}

	distance = tmin;

	return true;
}
