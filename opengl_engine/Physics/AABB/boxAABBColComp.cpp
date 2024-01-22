#include "boxAABBColComp.h"
#include "collisionsAABB.h"

#include <Assets/assetManager.h>
#include <Rendering/material.h>

BoxAABBColComp::BoxAABBColComp() : 
	CollisionComponent(CollisionType::BoxAABB, nullptr, &AssetManager::GetSingleMesh("default_cube"))
{
}

BoxAABBColComp::BoxAABBColComp(Box boxValues, const Transform* transformToAssociate, bool scaleBoxSizeWithTransform) :
	box(boxValues), useTransformScaleForBoxSize(scaleBoxSizeWithTransform),
	CollisionComponent(CollisionType::BoxAABB, transformToAssociate, &AssetManager::GetSingleMesh("default_cube"))
{
}

bool BoxAABBColComp::resolvePoint(const Vector3& point) const
{
	return CollisionsAABB::IntersectPoint(*this, point);
}

bool BoxAABBColComp::resolveRaycast(const Ray& raycast, RaycastHitInfos& outHitInfos) const
{
	return CollisionsAABB::IntersectRaycast(*this, raycast, outHitInfos);
}

bool BoxAABBColComp::resolveCollision(const CollisionComponent& otherCol) const
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

void BoxAABBColComp::drawDebug(Material& debugMaterial) const
{
	debugMaterial.getShader().setMatrix4("model", getModelMatrix().getAsFloatPtr());

	if (debugMesh)
	{
		debugMesh->draw();
	}
}

const Matrix4 BoxAABBColComp::getModelMatrix() const
{
	Box transform_box = getTransformedBox();
	Matrix4 matrix =
		Matrix4::createScale(transform_box.getHalfExtents() * 2.0f) *
		Matrix4::createTranslation(transform_box.getCenterPoint());
	return matrix;
}


Box BoxAABBColComp::getTransformedBox() const
{
	Box transformed_box;

	transformed_box.setCenterPoint((box.getCenterPoint() * associatedTransform->getScale()) + associatedTransform->getPosition());
	transformed_box.setHalfExtents(box.getHalfExtents() * (useTransformScaleForBoxSize ? associatedTransform->getScale() : Vector3::one));

	return transformed_box;
}
