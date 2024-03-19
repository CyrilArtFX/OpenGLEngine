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
	setPosition(Vector3{0.0f, 10.0f, 0.0f});
	setScale(0.005f);
	//setRotation(Quaternion::fromEuler(0.0f, Maths::toRadians(-90.0f), 0.0f));
}
