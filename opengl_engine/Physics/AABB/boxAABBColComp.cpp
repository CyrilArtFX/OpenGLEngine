#include "boxAABBColComp.h"
#include "collisionsAABB.h"

#include <Assets/assetManager.h>
#include <Rendering/material.h>

BoxAABBColComp::BoxAABBColComp() : 
	CollisionComponent(CollisionType::BoxAABB, nullptr, &AssetManager::GetSingleMesh("debug_cube"), false, "")
{
}

BoxAABBColComp::BoxAABBColComp(const Box& boxValues, Object* objectToAssociate, bool loadPersistent, std::string collisionChannel, bool scaleBoxSizeWithTransform, bool moveBoxCenterWithObjectScale) :
	box(boxValues), useTransformScaleForBoxSize(scaleBoxSizeWithTransform), useTransformScaleForBoxCenter(moveBoxCenterWithObjectScale),
	CollisionComponent(CollisionType::BoxAABB, objectToAssociate, &AssetManager::GetSingleMesh("debug_cube"), loadPersistent, collisionChannel)
{
}

void BoxAABBColComp::changeBox(const Box& boxValues)
{
	box = boxValues;
}


bool BoxAABBColComp::resolvePointIntersection(const Vector3& point) const
{
	return CollisionsAABB::IntersectPoint(*this, point);
}

bool BoxAABBColComp::resolveLineRaycastIntersection(const Ray& raycast, RaycastHitInfos& outHitInfos) const
{
	return CollisionsAABB::IntersectLineRaycast(*this, raycast, outHitInfos);
}

bool BoxAABBColComp::resolveAABBRaycastIntersection(const Box& raycast) const
{
	return CollisionsAABB::IntersectAABBRaycast(*this, raycast);
}

bool BoxAABBColComp::resolveCollisionIntersection(const CollisionComponent& otherCol) const
{
	switch (otherCol.getCollisionType())
	{
	case CollisionType::BoxAABB:
		{
		const BoxAABBColComp& other_col_as_aabb = static_cast<const BoxAABBColComp&>(otherCol);
		return CollisionsAABB::IntersectBoxAABB(*this, other_col_as_aabb);
		} //  {} are here to encapsulate the local variable other_col_as_aabb
		

	default:
		return false;
	}
}

bool BoxAABBColComp::resolveRigidbodyIntersection(const RigidbodyComponent& rigidbody, CollisionResponse& outResponse) const
{
	switch (rigidbody.getAssociatedCollision().getCollisionType())
	{
	case CollisionType::BoxAABB:
		return CollisionsAABB::CollideBodyBox(rigidbody, outResponse, *this);
	
	default:
		return false;
	}
}

bool BoxAABBColComp::resolveRigidbodySelfIntersection(const RigidbodyComponent& rigidbody, const RigidbodyComponent& selfRigidbody) const
{
	switch (rigidbody.getAssociatedCollision().getCollisionType())
	{
	case CollisionType::BoxAABB:
		return CollisionsAABB::CollideBodies(rigidbody, selfRigidbody);

	default:
		return false;
	}
}



void BoxAABBColComp::drawDebugMesh(Material& debugMaterial) const
{
	debugMaterial.getShader().setMatrix4("model", getModelMatrix().getAsFloatPtr());

	if (debugMesh)
	{
		debugMesh->draw(true);
	}
}

const Matrix4 BoxAABBColComp::getModelMatrix() const
{
	Box transform_box = getTransformedBox(true);
	Matrix4 matrix =
		Matrix4::createScale(transform_box.getHalfExtents() * 2.0f) *
		Matrix4::createTranslation(transform_box.getCenterPoint());
	return matrix;
}


Box BoxAABBColComp::getTransformedBox(bool forDrawDebug) const
{
	Box transformed_box;

	Vector3 center_factor = useTransformScaleForBoxCenter ? associatedObject->getScale() : Vector3::one;
	Vector3 scale_factor = useTransformScaleForBoxSize ? associatedObject->getScale() : Vector3::one;

	transformed_box.setCenterPoint((box.getCenterPoint() * center_factor) + associatedObject->getPosition());
	Vector3 half_extents = box.getHalfExtents() * scale_factor;
	//if (forDrawDebug) half_extents += Vector3{ 0.01f, 0.01f, 0.01f };
	transformed_box.setHalfExtents(half_extents);

	return transformed_box;
}

Vector3 BoxAABBColComp::getNormal(const Vector3& point) const
{
	//  this function can surely be greatly optimized by using maths
	//  I will need to check that later
	Box transformed_box = getTransformedBox();
	Vector3 box_min = transformed_box.getMinPoint();
	Vector3 box_max = transformed_box.getMaxPoint();

	Vector3 out_normal = Vector3::zero;

	if (point.x == box_min.x) out_normal.x = -1.0f;
	else if (point.x == box_max.x) out_normal.x = 1.0f;

	if (point.y == box_min.y) out_normal.y = -1.0f;
	else if (point.y == box_max.y) out_normal.y = 1.0f;

	if (point.z == box_min.z) out_normal.z = -1.0f;
	else if (point.z == box_max.z) out_normal.z = 1.0f;

	out_normal.normalize();
	return out_normal;
}