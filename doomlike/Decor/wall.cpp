#include "wall.h"
#include <Physics/physics.h>
#include <Physics/AABB/boxAABBColComp.h>


Wall::Wall(Vector3 position, FacingDirection facingDirection, bool hasCollision)
{
	setup(position, facingDirection, hasCollision);
}

void Wall::load()
{
	addModel(&AssetManager::GetModel("wall"));
}

void Wall::setup(Vector3 position, FacingDirection facingDirection, bool hasCollision)
{
	setPosition(position);


	switch (facingDirection)
	{
	case FacingDirection::FacingPositiveX:
		setRotation(Quaternion::fromEuler(0.0f, Maths::toRadians(90.0f), Maths::toRadians(-90.0f)));
		if (hasCollision)
			Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{-0.1f, 0.0f, 0.0f}, Vector3{0.1f, 0.5f, 0.5f} }, this, false, "solid"));
		break;

	case FacingDirection::FacingNegativeX:
		setRotation(Quaternion::fromEuler(0.0f, Maths::toRadians(90.0f), Maths::toRadians(90.0f)));
		if (hasCollision)
			Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.1f, 0.0f, 0.0f}, Vector3{0.1f, 0.5f, 0.5f} }, this, false, "solid"));
		break;

	case FacingDirection::FacingPositiveZ:
		setRotation(Quaternion::fromEuler(Maths::toRadians(90.0f), Maths::toRadians(90.0f), Maths::toRadians(90.0f)));
		if (hasCollision)
			Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, 0.0f, -0.1f}, Vector3{0.5f, 0.5f, 0.1f} }, this, false, "solid"));
		break;

	case FacingDirection::FacingNegativeZ:
		setRotation(Quaternion::fromEuler(Maths::toRadians(-90.0f), Maths::toRadians(90.0f), Maths::toRadians(90.0f)));
		if (hasCollision)
			Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, 0.0f, 0.1f}, Vector3{0.5f, 0.5f, 0.1f} }, this, false, "solid"));
		break;
	}
}