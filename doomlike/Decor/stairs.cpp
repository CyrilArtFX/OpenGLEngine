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



	switch (facingDirection)
	{
	case FacingDirection::FacingPositiveX:
		//  no rotation
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{ 1.03f, 1.11f, -0.93f }, Vector3::one }, this, false, "solid", false, false));
		break;

	case FacingDirection::FacingNegativeX:
		setRotation(Quaternion::fromEuler(Maths::toRadians(180.0f), 0.0f, 0.0f));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{ -1.03f, 1.11f, 0.93f }, Vector3::one }, this, false, "solid", false, false));
		break;

	case FacingDirection::FacingPositiveZ:
		setRotation(Quaternion::fromEuler(Maths::toRadians(270.0f), 0.0f, 0.0f));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{ 0.93f, 1.11f, 1.03f }, Vector3::one }, this, false, "solid", false, false));
		break;

	case FacingDirection::FacingNegativeZ:
		setRotation(Quaternion::fromEuler(Maths::toRadians(90.0f), 0.0f, 0.0f));
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{ -0.93f, 1.11f, -1.03f }, Vector3::one }, this, false, "solid", false, false));
		break;
	}

	addPositionRotated(Vector3{ 0.93f, -0.11f, -1.03f }); //  this allows to have the stairs origin at the center bottom

}