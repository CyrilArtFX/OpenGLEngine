#include "doomlikeLevelAdvanced.h"
#include <ServiceLocator/locator.h>

#include <Assets/assetManager.h>
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
	Renderer& renderer = Locator::getRenderer();

	renderer.SetClearColor(Color{ 50, 75, 75, 255 });

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
	

	//  decor - dynamic lights
	ceilLamp1 = static_cast<Lamp*>(&registerObject(new Lamp(Vector3{ -8.0f, 10.0f, -8.0f }, true, *this, 0.12f, true)));
	ceilLamp2 = static_cast<Lamp*>(&registerObject(new Lamp(Vector3{  8.0f, 10.0f, -8.0f }, true, *this, 0.37f, true)));
	ceilLamp3 = static_cast<Lamp*>(&registerObject(new Lamp(Vector3{ -8.0f, 10.0f,  8.0f }, true, *this, 0.56f, true)));
	ceilLamp4 = static_cast<Lamp*>(&registerObject(new Lamp(Vector3{  8.0f, 10.0f,  8.0f }, true, *this, 0.81f, true)));
	ceilLamp5 = static_cast<Lamp*>(&registerObject(new Lamp(Vector3{ -8.0f, 10.0f,  0.0f }, true, *this, 0.25f, true)));
	ceilLamp6 = static_cast<Lamp*>(&registerObject(new Lamp(Vector3{  8.0f, 10.0f,  0.0f }, true, *this, 0.43f, true)));
	ceilLamp7 = static_cast<Lamp*>(&registerObject(new Lamp(Vector3{  0.0f, 10.0f, -8.0f }, true, *this, 0.72f, true)));
	ceilLamp8 = static_cast<Lamp*>(&registerObject(new Lamp(Vector3{  0.0f, 10.0f,  8.0f }, true, *this, 0.97f, true)));
	floorLamp = static_cast<Lamp*>(&registerObject(new Lamp(Vector3{  6.0f,  0.0f,  0.0f }, false, *this, 0.85f, false)));


	//  elevator
	elevator.addModel(&AssetManager::GetModel("crate"));
	registerObject(&elevator);
	elevator.setup(Vector3{ 2.5f, 0.1f, 0.0f }, Vector3{ 2.5f, 6.9f, 0.0f }, 4.0f, 2.0f);
	elevator.pause();


	//  trigger zones
	elevatorUpZone.setup(Vector3{ 2.5f, 1.0f, 0.0f }, Vector3{ 0.3f, 0.3f, 0.3f });
	elevatorUpZone.onPlayerEnter.registerObserver(this, Bind_0(&DoomlikeLevelAdvanced::onPlayerEnterElevatorUpZone));
	enemySpawnZone.setup(Vector3{ 0.0f, 7.5f, 0.0f }, Vector3{ 0.2f, 0.2f, 0.2f });
	enemySpawnZone.onPlayerEnter.registerObserver(this, Bind_0(&DoomlikeLevelAdvanced::onPlayerEnterEnemySpawnZone));


	//  static lights
	globalLight.load(Color{ 255, 238, 209, 255 }, Vector3::unitY, 0.15f, 0.0f);
	registerLight(&globalLight);


	//  spawn point
	spawnPosition = Vector3{ 9.0f, 0.0f, 0.0f };
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
	elevatorTimer = 0.1f;
}

void DoomlikeLevelAdvanced::onPlayerEnterEnemySpawnZone()
{
	enemySpawnZone.onPlayerEnter.unregisterObserver(this);
	enemySpawnZone.disableZone();

	ceilLamp1->changeStatus(true);
	ceilLamp2->changeStatus(true);
	ceilLamp3->changeStatus(true);
	ceilLamp4->changeStatus(true);
	ceilLamp5->changeStatus(true);
	ceilLamp6->changeStatus(true);
	ceilLamp7->changeStatus(true);
	ceilLamp8->changeStatus(true);
	floorLamp->changeStatus(false);

	registerObject(new Enemy()).setPosition(Vector3{ -5.0f, 7.5f, -5.0f });
	registerObject(new Enemy()).setPosition(Vector3{ -5.0f, 7.5f,  5.0f });
	registerObject(new Enemy()).setPosition(Vector3{  5.0f, 7.5f, -5.0f });
	registerObject(new Enemy()).setPosition(Vector3{  5.0f, 7.5f,  5.0f });
}
