#include "floorceiling.h"
#include <ServiceLocator/locator.h>
#include <ServiceLocator/physics.h>
#include <Physics/AABB/boxAABBColComp.h>

FloorObj::FloorObj(Vector3 position, bool isWood, bool hasCollision)
{
	setup(position, isWood, hasCollision);
}

void FloorObj::load()
{
}

void FloorObj::setup(Vector3 position, bool isWood, bool hasCollision)
{
	Physics& physics = Locator::getPhysics();

	addModel(&AssetManager::GetModel(isWood ? "floor_wood" : "floor"));

	setPosition(position);
	if (hasCollision)
		physics.CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, -0.1f, 0.0f}, Vector3{0.5f, 0.1f, 0.5f} }, this, false, "solid"));
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
	Physics& physics = Locator::getPhysics();

	setPosition(position);
	setRotation(Quaternion::fromEuler(0.0f, Maths::toRadians(180.0f), 0.0f));
	if (hasCollision)
		physics.CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, 0.2f, 0.0f}, Vector3{0.5f, 0.2f, 0.5f} }, this, false, "solid"));
	//  ceiling collision a bit thicker cause otherwise player would be able to pass through it thanks to step mechanic
	//  (might need to investigate this issue)
}