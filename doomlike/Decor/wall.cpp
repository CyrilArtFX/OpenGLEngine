#include "wall.h"
#include <Physics/physics.h>
#include <Physics/AABB/boxAABBColComp.h>


Wall::Wall(Vector3 position, FacingDirection facingDirection, WallSize size, bool hasCollision)
{
	setup(position, facingDirection, size, hasCollision);
}

void Wall::load()
{
}

void Wall::setup(Vector3 position, FacingDirection facingDirection, WallSize size, bool hasCollision)
{
	float col_size = 0.0f;
	switch (size)
	{
	case WallSize::WallSmall:
		addModel(&AssetManager::GetModel("wall_small"));
		col_size = 1.25f;
		break;
	case WallSize::WallBig:
		addModel(&AssetManager::GetModel("wall_big"));
		col_size = 2.5f;
		break;
	}

	setPosition(position);

	switch (facingDirection)
	{
	case FacingDirection::FacingPositiveX:
		setRotation(Quaternion::fromEuler(0.0f, Maths::toRadians(90.0f), Maths::toRadians(-90.0f)));
		if (hasCollision)
			Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{-0.1f, 0.0f, 0.0f}, Vector3{0.1f, col_size, col_size} }, this, false, "solid"));
		break;

	case FacingDirection::FacingNegativeX:
		setRotation(Quaternion::fromEuler(0.0f, Maths::toRadians(90.0f), Maths::toRadians(90.0f)));
		if (hasCollision)
			Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.1f, 0.0f, 0.0f}, Vector3{0.1f, col_size, col_size} }, this, false, "solid"));
		break;

	case FacingDirection::FacingPositiveZ:
		setRotation(Quaternion::fromEuler(Maths::toRadians(90.0f), Maths::toRadians(90.0f), Maths::toRadians(90.0f)));
		if (hasCollision)
			Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, 0.0f, -0.1f}, Vector3{col_size, col_size, 0.1f} }, this, false, "solid"));
		break;

	case FacingDirection::FacingNegativeZ:
		setRotation(Quaternion::fromEuler(Maths::toRadians(-90.0f), Maths::toRadians(90.0f), Maths::toRadians(90.0f)));
		if (hasCollision)
			Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, 0.0f, 0.1f}, Vector3{col_size, col_size, 0.1f} }, this, false, "solid"));
		break;
	}
}