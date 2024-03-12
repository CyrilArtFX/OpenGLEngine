#include "doomlikeLevelStart.h"

#include <Assets/assetManager.h>
#include <Physics/physics.h>

#include <Maths/vector3.h>
#include <Utils/Color.h>

#include <Physics/AABB/boxAABBColComp.h>


DoomlikeLevelStart::DoomlikeLevelStart()
{
}

void DoomlikeLevelStart::loadScene()
{
	renderer->setClearColor(Color{ 50, 75, 75, 255 });


	//  static objects
	ground.addModel(&AssetManager::GetModel("ground"));
	wall.addModel(&AssetManager::GetModel("wall"));
	wall2.addModel(&AssetManager::GetModel("wall"));

	registerObject(&ground);
	registerObject(&wall);
	registerObject(&wall2);

	ground.setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	wall.setPosition(Vector3{ 5.0f, 1.0f, 0.0f });
	wall.setRotation(Quaternion::fromEuler(0.0f, Maths::toRadians(90.0f), Maths::toRadians(90.0f)));
	wall2.setPosition(Vector3{ 0.0f, 1.0f, 5.0f });
	wall2.setRotation(Quaternion::fromEuler(Maths::toRadians(-90.0f), Maths::toRadians(90.0f), Maths::toRadians(90.0f)));


	//  collisions for static objects
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, -0.1f, 0.0f}, Vector3{5.0f, 0.1f, 5.0f} }, &ground, false, "solid"));
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.1f, 0.0f, 0.0f}, Vector3{0.1f, 1.0f, 1.0f} }, &wall, false, "solid"));
	Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, 0.0f, 0.1f}, Vector3{1.0f, 1.0f, 0.1f} }, &wall2, false, "solid"));


	//  static lights
	Vector3 dir_light{ -0.5f, -1.0f, 0.75f };
	globalLight.load(Color::white, Vector3::normalize(dir_light), 0.6f, 0.3f);
	registerLight(&globalLight);
	RaycastHitInfos out;
	Physics::LineRaycast(Vector3::zero, dir_light, {"aaa"}, out, -1.0f);


	//  spawn point
	spawnPosition = Vector3{ 0.0f, 0.0f, 0.0f };
}

void DoomlikeLevelStart::updateScene(float dt)
{
}

void DoomlikeLevelStart::unloadScene()
{
}
