#include "floorceiling.h"
#include <Physics/physics.h>
#include <Physics/AABB/boxAABBColComp.h>

FloorObj::FloorObj(Vector3 position, bool hasCollision)
{
	setup(position, hasCollision);
}

void FloorObj::load()
{
	addModel(&AssetManager::GetModel("floor"));
}

void FloorObj::setup(Vector3 position, bool hasCollision)
{
	setPosition(position);
	if (hasCollision)
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, -0.1f, 0.0f}, Vector3{2.5f, 0.1f, 2.5f} }, this, false, "solid"));
}



Ceiling::Ceiling(Vector3 position, bool hasCollision)
{
	setup(position, hasCollision);
}

void Ceiling::load()
{
	addModel(&AssetManager::GetModel("ceiling"));
}

void Ceiling::setup(Vector3 position, bool hasCollision)
{
	setPosition(position);
	setRotation(Quaternion::fromEuler(0.0f, Maths::toRadians(180.0f), 0.0f));
	if (hasCollision)
		Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, 0.2f, 0.0f}, Vector3{2.5f, 0.2f, 2.5f} }, this, false, "solid"));
	//  ceiling collision a bit thicker cause otherwise player would be able to pass through it thanks to step mechanic
	//  (might need to investigate this issue)
}