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

bool BoxAABBColComp::resolveAABBSweepRaycastIntersection(const Ray& raycast, const Box& boxRaycast, RaycastHitInfos& outHitInfos) const
{
	return CollisionsAABB::IntersectAABBSweepRaycast(*this, raycast, boxRaycast, outHitInfos);
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

Vector3 BoxAABBColComp::getCenterDownPos() const
{
	Box transformed_box = getTransformedBox();
	Vector3 center_down = transformed_box.getCenterPoint();
	center_down += Vector3{ 0.0f, -transformed_box.getHalfExtents().y, 0.0f };
	return center_down;
}

Box BoxAABBColComp::getEncapsulatingBox() const
{
	return getTransformedBox();
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
	Box transformed_box = getTransformedBox();
	return transformed_box.getNormalAtPoint(point);
}