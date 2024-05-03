#include "doomlikeLevelAdvanced.h"

#include <Assets/assetManager.h>
#include <Physics/physics.h>
#include <Physics/AABB/boxAABBColComp.h>

#include <Maths/vector3.h>
#include <Utils/color.h>


using Wall::WallObj;
using Stairs::StairsObj;


DoomlikeLevelAdvanced::DoomlikeLevelAdvanced()
{
}

void DoomlikeLevelAdvanced::loadScene()
{
	renderer->setClearColor(Color{ 50, 75, 75, 255 });

	//  floors, ceilings, walls and stairs
	registerObject(new FloorObj(Vector3{ 0.0f, 0.0f, 0.0f }, false)).setScale(Vector3{ 20.0f, 1.0f, 20.0f });
	registerObject(new FloorObj(Vector3{ 0.0f, 7.0f, 0.0f }, true)).setScale(Vector3{ 2.5f, 1.0f, 2.5f });
	registerObject(new Ceiling(Vector3{ 0.0f, 10.0f, 0.0f })).setScale(Vector3{ 20.0f, 1.0f, 20.0f });

	registerObject(new WallObj(Vector3{   0.0f, 3.5f, -1.25f }, Wall::FacingDirection::FacingNegativeZ, Vector2{ 2.5f, 7.0f }));
	registerObject(new WallObj(Vector3{  1.25f, 3.5f,   0.0f }, Wall::FacingDirection::FacingPositiveX, Vector2{ 2.5f, 7.0f }));
	registerObject(new WallObj(Vector3{ -1.25f, 3.5f,   0.0f }, Wall::FacingDirection::FacingNegativeX, Vector2{ 2.5f, 7.0f }));
	registerObject(new WallObj(Vector3{   0.0f, 3.5f,  1.25f }, Wall::FacingDirection::FacingPositiveZ, Vector2{ 2.5f, 7.0f }));

	registerObject(new WallObj(Vector3{   0.0f, 5.0f,  10.0f }, Wall::FacingDirection::FacingNegativeZ, Vector2{ 20.0f, 10.0f }));
	registerObject(new WallObj(Vector3{ -10.0f, 5.0f,   0.0f }, Wall::FacingDirection::FacingPositiveX, Vector2{ 20.0f, 10.0f }));
	registerObject(new WallObj(Vector3{  10.0f, 5.0f,   0.0f }, Wall::FacingDirection::FacingNegativeX, Vector2{ 20.0f, 10.0f }));
	registerObject(new WallObj(Vector3{   0.0f, 5.0f, -10.0f }, Wall::FacingDirection::FacingPositiveZ, Vector2{ 20.0f, 10.0f }));
	

	//  decor
	registerObject(new Lamp(Vector3{ -8.0f, 10.0f, -8.0f }, true, *this, 0.12f, true));
	registerObject(new Lamp(Vector3{  8.0f, 10.0f, -8.0f }, true, *this, 0.37f, true));
	registerObject(new Lamp(Vector3{ -8.0f, 10.0f,  8.0f }, true, *this, 0.56f, true));
	registerObject(new Lamp(Vector3{  8.0f, 10.0f,  8.0f }, true, *this, 0.81f, true));
	registerObject(new Lamp(Vector3{ -8.0f, 10.0f,  0.0f }, true, *this, 0.25f, true));
	registerObject(new Lamp(Vector3{  8.0f, 10.0f,  0.0f }, true, *this, 0.43f, true));
	registerObject(new Lamp(Vector3{  0.0f, 10.0f, -8.0f }, true, *this, 0.72f, true));
	registerObject(new Lamp(Vector3{  0.0f, 10.0f,  8.0f }, true, *this, 0.97f, true));


	//  elevator
	elevator.addModel(&AssetManager::GetModel("crate"));
	registerObject(&elevator);
	elevator.setup(Vector3{ 0.0f, 0.1f, -2.5f }, Vector3{ 0.0f, 6.9f, -2.5f }, 4.0f, 2.0f);
	elevator.pause();


	//  trigger zones
	elevatorUpZone.setup(Vector3{ 0.0f, 1.0f, -2.0f }, Vector3{ 0.2f, 0.2f, 0.2f });
	elevatorUpZone.onPlayerEnter.registerObserver(this, Bind_0(&DoomlikeLevelAdvanced::onPlayerEnterElevatorUpZone));


	//  static lights
	globalLight.load(Color{ 255, 238, 209, 255 }, Vector3::unitY, 0.35f, 0.0f);
	registerLight(&globalLight);


	//  spawn point
	spawnPosition = Vector3{ 0.0f, 0.0f, -9.0f };
}

void DoomlikeLevelAdvanced::updateScene(float dt)
{
	if (elevatorTimer <= 0.0f) return;
	elevatorTimer -= dt;
	if (elevatorTimer <= 0.0f)
	{
		elevator.resume();
	}
}

void DoomlikeLevelAdvanced::unloadScene()
{
}

void DoomlikeLevelAdvanced::onPlayerEnterElevatorUpZone()
{
	elevatorUpZone.onPlayerEnter.unregisterObserver(this);
	elevatorUpZone.disableZone();
	elevatorTimer = 0.5f;
}

void DoomlikeLevelAdvanced::onPlayerEnterEnemySpawnZone()
{
}
