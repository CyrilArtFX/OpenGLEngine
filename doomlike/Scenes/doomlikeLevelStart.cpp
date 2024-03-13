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
	registerObject(&floor);
	registerObject(&wall1);
	registerObject(&wall2);
	registerObject(&ceiling);

	floor.setup(Vector3::zero);
	wall1.setup(Vector3{ 1.25f, 1.25f, 2.5f }, FacingDirection::FacingNegativeZ);
	wall2.setup(Vector3{ 2.5f, 1.25f, 1.25f }, FacingDirection::FacingNegativeX);
	ceiling.setup(Vector3{ 0.0f, 2.5f, 0.0f });



	//  static lights
	globalLight.load(Color::white, Vector3::unitY, 0.7f, 0.0f);
	registerLight(&globalLight);


	//  spawn point
	spawnPosition = Vector3{ 0.0f, 0.0f, 0.0f };
}

void DoomlikeLevelStart::updateScene(float dt)
{
}

void DoomlikeLevelStart::unloadScene()
{
}
