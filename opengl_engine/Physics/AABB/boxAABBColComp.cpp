#include "boxAABBColComp.h"
#include "collisionsAABB.h"

#include <Assets/assetManager.h>
#include <Rendering/material.h>

BoxAABBColComp::BoxAABBColComp() : 
	CollisionComponent(CollisionType::BoxAABB, nullptr, &AssetManager::GetSingleMesh("debug_cube"))
{
}

BoxAABBColComp::BoxAABBColComp(const Box& boxValues, const Transform* transformToAssociate, bool scaleBoxSizeWithTransform) :
	box(boxValues), useTransformScaleForBoxSize(scaleBoxSizeWithTransform),
	CollisionComponent(CollisionType::BoxAABB, transformToAssociate, &AssetManager::GetSingleMesh("debug_cube"))
{
}

bool BoxAABBColComp::resolvePointIntersection(const Vector3& point) const
{
	return CollisionsAABB::IntersectPoint(*this, point);
}

bool BoxAABBColComp::resolveRaycastIntersection(const Ray& raycast, RaycastHitInfos& outHitInfos) const
{
	return CollisionsAABB::IntersectRaycast(*this, raycast, outHitInfos);
}

bool BoxAABBColComp::resolveCollisionIntersection(const CollisionComponent& otherCol) const
{
	switch (otherCol.getCollisionType())
	{
	case CollisionType::BoxAABB:
		{
		const BoxAABBColComp& other_col_as_aabb = static_cast<const BoxAABBColComp&>(otherCol);
		if (getUseCCD() && !otherCol.getUseCCD())
		{
			return CollisionsAABB::IntersectBoxAABBwithCCD(*this, other_col_as_aabb);
		}
		else if (!getUseCCD() && otherCol.getUseCCD())
		{
			return CollisionsAABB::IntersectBoxAABBwithCCD(other_col_as_aabb, *this);
		}
		else
		{
			return CollisionsAABB::IntersectBoxAABB(*this, other_col_as_aabb);
		}
		} //  {} are here to encapsulate the local variable other_col_as_aabb
		

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

	transformed_box.setCenterPoint((box.getCenterPoint() * associatedTransform->getScale()) + associatedTransform->getPosition());
	Vector3 scale_factors = useTransformScaleForBoxSize ? associatedTransform->getScale() : Vector3::one;
	Vector3 half_extents = box.getHalfExtents() * scale_factors;
	if (forDrawDebug) half_extents += Vector3{ 0.01f, 0.01f, 0.01f };
	transformed_box.setHalfExtents(half_extents);

	return transformed_box;
}

Vector3 BoxAABBColComp::getLastFrameTransformedPos() const
{
	 return (box.getCenterPoint() * associatedTransform->getScale()) + getLastFramePos();
}
