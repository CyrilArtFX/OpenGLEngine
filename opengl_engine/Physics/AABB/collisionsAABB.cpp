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

bool CollisionsAABB::CollideBodyBox(const RigidbodyComponent& bodyAABB, CollisionResponse& outBodyResponse, const BoxAABBColComp& boxAABB)
{
	bool interpolate = false;
	const BoxAABBColComp& body_box_aabb = static_cast<const BoxAABBColComp&>(bodyAABB.getAssociatedCollision());

	if (bodyAABB.getUseCCD())
	{
		const Box& ccd_box = body_box_aabb.getTransformedBox();
		const Vector3& ccd_pos_last_frame = body_box_aabb.getLastFrameTransformedPos();
		const Box& static_box = boxAABB.getTransformedBox();
		float hit_distance = 0.0f;
		
		interpolate = CCDBoxIntersection(ccd_box, ccd_pos_last_frame, static_box, hit_distance);

		if (interpolate && bodyAABB.isPhysicsActivated())
		{
			//  set outBodyResponse
			Vector3 body_vel = ccd_box.getCenterPoint() - ccd_pos_last_frame;
			float body_vel_length = body_vel.length();
			body_vel.normalize();
			outBodyResponse.repulsion += -body_vel * (body_vel_length - hit_distance);
		}
	}
	else
	{
		interpolate = IntersectBoxAABB(body_box_aabb, boxAABB);

		if (interpolate && bodyAABB.isPhysicsActivated())
		{
			//  set outBodyResponse
			const Box& body_box = body_box_aabb.getTransformedBox();
			const Box& static_box = boxAABB.getTransformedBox();
			Vector3 body_to_box = static_box.getCenterPoint() - body_box.getCenterPoint();
			body_to_box.clampToOne();
			body_to_box *= (body_box.getHalfExtents() + static_box.getHalfExtents());
			outBodyResponse.repulsion += -body_to_box;
		}
	}

	return interpolate;
}

bool CollisionsAABB::CollideBodies(const RigidbodyComponent& bodyAABBa, CollisionResponse& outBodyAResponse, const RigidbodyComponent& bodyAABBb, CollisionResponse& outBodyBResponse)
{
	return false;
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

	//  if tmin > length, ray (line) is intersecting AABB, but the whole AABB is after the end of the raycast
	if (tmin > ray_length)
	{
		return false;
	}

	distance = tmin;

	return true;
}

bool CollisionsAABB::CCDBoxIntersection(const Box& boxCCD, const Vector3& ccdLastFramePos, const Box& box, float& distance)
{
	Vector3 box_ccd_pos = boxCCD.getCenterPoint();

	Box box_static = box;
	box_static.addHalfExtents(boxCCD);

	Ray ray;
	ray.setupWithStartEnd(ccdLastFramePos, box_ccd_pos);

	float hit_distance = 0.0f;

	bool intersect = BoxRayIntersection(box, ray, hit_distance);

	return intersect;
}
