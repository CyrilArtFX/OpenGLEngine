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
	Box box_b = otherBoxAABB.getTransformedBox();

	return BoxesIntersection(box_a, box_b);
}

bool CollisionsAABB::CollideBodyBox(const RigidbodyComponent& bodyAABB, CollisionResponse& outBodyResponse, const BoxAABBColComp& boxAABB)
{
	bool interpolate = false;
	const BoxAABBColComp& body_box_aabb = static_cast<const BoxAABBColComp&>(bodyAABB.getAssociatedCollision());

	if (!bodyAABB.getUseCCD())
	{
		Box body_box = body_box_aabb.getTransformedBox();
		body_box.setCenterPoint(body_box.getCenterPoint() + bodyAABB.getAnticipatedMovement());
		const Box& static_box = boxAABB.getTransformedBox();
		interpolate = BoxesIntersection(body_box, static_box);
	}

	//  if the body (without ccd) intersect the collision, the test with ccd is use for it to compute repulsion
	if (bodyAABB.getUseCCD() || interpolate)
	{
		const Box& ccd_box = body_box_aabb.getTransformedBox();
		const Vector3& ccd_pos_next_frame = ccd_box.getCenterPoint() + bodyAABB.getAnticipatedMovement();
		const Box& static_box = boxAABB.getTransformedBox();
		float hit_distance = 0.0f;
		
		interpolate = CCDBoxIntersection(ccd_box, ccd_pos_next_frame, static_box, hit_distance);

		if (interpolate && bodyAABB.isPhysicsActivated())
		{
			//  set outBodyResponse
			Vector3 body_vel = bodyAABB.getAnticipatedMovement();
			float body_vel_length = body_vel.length();
			body_vel.normalize();
			outBodyResponse.repulsion = -body_vel * (body_vel_length - hit_distance);
			Vector3 test = outBodyResponse.repulsion;
		}
	}

	return interpolate;
}

bool CollisionsAABB::CollideBodies(const RigidbodyComponent& bodyAABBa, CollisionResponse& outBodyAResponse, const RigidbodyComponent& bodyAABBb, CollisionResponse& outBodyBResponse)
{
	return false;
}


bool CollisionsAABB::BoxesIntersection(const Box& boxA, const Box& boxB)
{
	Vector3 box_a_min = boxA.getMinPoint();
	Vector3 box_a_max = boxA.getMaxPoint();

	Vector3 box_b_min = boxB.getMinPoint();
	Vector3 box_b_max = boxB.getMaxPoint();

	return box_a_min < box_b_max && box_a_max > box_b_min;
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

bool CollisionsAABB::CCDBoxIntersection(const Box& boxCCD, Vector3 ccdNextFramePos, const Box& box, float& distance)
{
	Vector3 box_ccd_pos = boxCCD.getCenterPoint();

	if (box_ccd_pos == ccdNextFramePos)
	{
		//  if the ccd_box is not moving, that means it's movement has already been completely reversed by another collision this frame,
		//  so it will be at the exact same place that previous frame, where it wasn't colliding with any static collision so it can't collide with this one
		return false;
	}

	Box box_static = box;
	box_static.addHalfExtents(boxCCD);

	Ray ray;
	ray.setupWithStartEnd(box_ccd_pos, ccdNextFramePos);

	bool intersect = BoxRayIntersection(box_static, ray, distance);

	return intersect;
}
