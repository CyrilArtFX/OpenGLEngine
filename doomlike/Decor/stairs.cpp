#include "stairs.h"
#include <Physics/physics.h>
#include <Physics/AABB/boxAABBColComp.h>

using Stairs::FacingDirection;
using Stairs::StairsObj;


StairsObj::StairsObj(Vector3 position, Stairs::FacingDirection facingDirection)
{
	setup(position, facingDirection);
}

void StairsObj::load()
{
	addModel(&AssetManager::GetModel("stairs"));
}

void StairsObj::setup(Vector3 position, Stairs::FacingDirection facingDirection)
{
	setPosition(position);
	setScale(0.0044f); //  this allows to have the stairs fitting in a 2*2*2 box

	Vector3 stairs_center;



	switch (facingDirection)
	{
	case FacingDirection::FacingPositiveX:
		//  no rotation

		stairs_center = Vector3{ 1.03f, 1.11f, -0.93f };
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, 0.0f, -0.9f}, Vector3{1.0f, 1.0f, 0.1f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, 0.0f, 0.9f}, Vector3{1.0f, 1.0f, 0.1f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.625f, -0.875f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.375f, -0.625f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.125f, -0.375f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{-0.125f, -0.125f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{-0.375f, 0.125f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{-0.625f, 0.375f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{-0.875f, 0.625f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));

		break;

	case FacingDirection::FacingNegativeX:
		setRotation(Quaternion::fromEuler(Maths::toRadians(180.0f), 0.0f, 0.0f));

		stairs_center = Vector3{ -1.03f, 1.11f, 0.93f };
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, 0.0f, -0.9f}, Vector3{1.0f, 1.0f, 0.1f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, 0.0f, 0.9f}, Vector3{1.0f, 1.0f, 0.1f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{-0.625f, -0.875f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{-0.375f, -0.625f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{-0.125f, -0.375f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.125f, -0.125f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.375f, 0.125f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.625f, 0.375f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.875f, 0.625f, 0.0f}, Vector3{0.125f, 0.125f, 0.8f} }, this, false, "solid", false, false));

		break;

	case FacingDirection::FacingPositiveZ:
		setRotation(Quaternion::fromEuler(Maths::toRadians(270.0f), 0.0f, 0.0f));

		stairs_center = Vector3{ 0.93f, 1.11f, 1.03f };
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{-0.9f, 0.0f, 0.0f}, Vector3{0.1f, 1.0f, 1.0f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.9f, 0.0f, 0.0f}, Vector3{0.1f, 1.0f, 1.0f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, -0.875f, 0.625f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, -0.625f, 0.375f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, -0.375f, 0.125f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, -0.125f, -0.125f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, 0.125f, -0.375f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, 0.375f, -0.625f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, 0.625f, -0.875f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));

		break;

	case FacingDirection::FacingNegativeZ:
		setRotation(Quaternion::fromEuler(Maths::toRadians(90.0f), 0.0f, 0.0f));

		stairs_center = Vector3{ -0.93f, 1.11f, -1.03f };
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{-0.9f, 0.0f, 0.0f}, Vector3{0.1f, 1.0f, 1.0f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.9f, 0.0f, 0.0f}, Vector3{0.1f, 1.0f, 1.0f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, -0.875f, -0.625f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, -0.625f, -0.375f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, -0.375f, -0.125f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, -0.125f, 0.125f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, 0.125f, 0.375f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, 0.375f, 0.625f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ stairs_center + Vector3{0.0f, 0.625f, 0.875f}, Vector3{0.8f, 0.125f, 0.125f} }, this, false, "solid", false, false));

		break;
	}

	addPositionRotated(Vector3{ 0.93f, -0.11f, -1.03f }); //  this allows to have the stairs origin at the center bottom

}