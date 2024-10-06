#include "boxAABBColComp.h"
#include "collisionsAABB.h"

#include <ServiceLocator/locator.h>
#include <ServiceLocator/audio.h>

#include <Assets/assetManager.h>
#include <Rendering/material.h>

BoxAABBColComp::BoxAABBColComp() :
	CollisionComponent(CollisionShape::BoxAABB, CollisionType::Solid, nullptr, & AssetManager::GetSingleMesh("debug_cube"), false, "")
{
}

BoxAABBColComp::BoxAABBColComp(const Box& boxValues, Object* objectToAssociate, bool loadPersistent, std::string collisionChannel, CollisionType collisionType, bool scaleBoxSizeWithTransform, bool moveBoxCenterWithObjectScale) :
	box(boxValues), useTransformScaleForBoxSize(scaleBoxSizeWithTransform), useTransformScaleForBoxCenter(moveBoxCenterWithObjectScale),
	CollisionComponent(CollisionShape::BoxAABB, collisionType, objectToAssociate, &AssetManager::GetSingleMesh("debug_cube"), loadPersistent, collisionChannel)
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

bool BoxAABBColComp::resolveAABBSweepRaycastIntersection(const Ray& raycast, const Box& boxRaycast, RaycastHitInfos& outHitInfos, bool forCollisionTest) const
{
	return CollisionsAABB::IntersectAABBSweepRaycast(*this, raycast, boxRaycast, outHitInfos, forCollisionTest);
}



void BoxAABBColComp::drawDebugMesh(Material& debugMaterial) const
{
	debugMaterial.getShader().setMatrix4("model", getModelMatrix().getAsFloatPtr());

	if (debugMesh)
	{
		debugMesh->draw(true);
	}
}

void BoxAABBColComp::onAssociatedTransformUpdated()
{
	if (!isAudioCollision) return;

	Audio& audio = Locator::getAudio();
	
	Transform audio_col_transform;
	audio_col_transform.setPosition(associatedObject->getPosition() + box.getCenterPoint());
	audio_col_transform.setScale(associatedObject->getScale() * box.getHalfExtents());

	audio.SetCollisionTransform(audioCollisionIndex, audio_col_transform);
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

void BoxAABBColComp::setupAudioCollision(const AudioCollisionOcclusion& audioCollisionType)
{
	if (isAudioCollision) return;
	isAudioCollision = true;

	Audio& audio = Locator::getAudio();
	audioCollisionIndex = audio.CreateCollision(6, 24);

	// b/f > backward/forward (X axis)  | b/t > bottom/top (Y axis)  | l/r > left/right (Z axis)
	const Vector3 vertex_bbl{ -1.0f, -1.0f, -1.0f };
	const Vector3 vertex_bbr{ -1.0f, -1.0f,  1.0f };
	const Vector3 vertex_btl{ -1.0f,  1.0f, -1.0f };
	const Vector3 vertex_btr{ -1.0f,  1.0f,  1.0f };
	const Vector3 vertex_fbl{  1.0f, -1.0f, -1.0f };
	const Vector3 vertex_fbr{  1.0f, -1.0f,  1.0f };
	const Vector3 vertex_ftl{  1.0f,  1.0f, -1.0f };
	const Vector3 vertex_ftr{  1.0f,  1.0f,  1.0f };
	
	audio.AddPolygonToCollision(audioCollisionIndex, audioCollisionType, true,
		{ vertex_bbl, vertex_bbr, vertex_btl, vertex_btr }); //  backward polygon
	audio.AddPolygonToCollision(audioCollisionIndex, audioCollisionType, true,
		{ vertex_fbl, vertex_fbr, vertex_ftl, vertex_ftr }); //  forward polygon
	audio.AddPolygonToCollision(audioCollisionIndex, audioCollisionType, true,
		{ vertex_bbl, vertex_bbr, vertex_fbl, vertex_fbr }); //  bottom polygon
	audio.AddPolygonToCollision(audioCollisionIndex, audioCollisionType, true,
		{ vertex_btl, vertex_btr, vertex_ftl, vertex_ftr }); //  top polygon
	audio.AddPolygonToCollision(audioCollisionIndex, audioCollisionType, true,
		{ vertex_bbl, vertex_btl, vertex_fbl, vertex_ftl }); //  left polygon
	audio.AddPolygonToCollision(audioCollisionIndex, audioCollisionType, true,
		{ vertex_bbr, vertex_btr, vertex_fbr, vertex_ftr }); //  left polygon

	associatedObject->onTransformUpdated.registerObserver(this, Bind_0(&BoxAABBColComp::onAssociatedTransformUpdated));

	onAssociatedTransformUpdated(); //  call it at audio collision setup to set the audio collision transform
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