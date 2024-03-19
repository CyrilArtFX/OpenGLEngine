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

	//  floors, ceilings and walls
	registerObject(new FloorObj(Vector3{ 0.0f, 0.0f,  2.5f })).setScale(Vector3{ 5.0f, 1.0f, 10.0f });
	registerObject(new FloorObj(Vector3{ 0.0f, 0.0f, 15.0f })).setScale(Vector3{ 15.0f, 1.0f, 15.0f });
	registerObject(new Ceiling(Vector3{ 0.0f, 3.0f,  2.5f })).setScale(Vector3{ 5.0f, 1.0f, 10.0f });
	registerObject(new Ceiling(Vector3{ 0.0f, 5.0f, 15.0f })).setScale(Vector3{ 15.0f, 1.0f, 15.0f });

	registerObject(new Wall(Vector3{ 0.0f, 1.5f, -2.5f }, FacingDirection::FacingPositiveZ, Vector2{ 5.0f, 3.0f }));
	registerObject(new Wall(Vector3{ -2.5f, 1.5f, 2.5f }, FacingDirection::FacingPositiveX, Vector2{ 10.0f, 3.0f }));
	registerObject(new Wall(Vector3{ 2.5f, 1.5f, 2.5f }, FacingDirection::FacingNegativeX, Vector2{ 10.0f, 3.0f }));

	registerObject(new Wall(Vector3{ -5.0f, 2.5f, 7.5f }, FacingDirection::FacingPositiveZ, Vector2{ 5.0f, 5.0f }));
	registerObject(new Wall(Vector3{ 0.0f, 4.0f, 7.5f }, FacingDirection::FacingPositiveZ, Vector2{ 5.0f, 2.0f }));
	registerObject(new Wall(Vector3{ 5.0f, 2.5f, 7.5f }, FacingDirection::FacingPositiveZ, Vector2{ 5.0f, 5.0f }));
	registerObject(new Wall(Vector3{ -7.5f, 2.5f, 15.0f }, FacingDirection::FacingPositiveX, Vector2{ 15.0f, 5.0f }));
	registerObject(new Wall(Vector3{ 7.5f, 2.5f, 15.0f }, FacingDirection::FacingNegativeX, Vector2{ 15.0f, 5.0f }));
	registerObject(new Wall(Vector3{ 0.0f, 2.5f, 22.5f }, FacingDirection::FacingNegativeZ, Vector2{ 15.0f, 5.0f }));

	registerObject(new Wall(Vector3{ -2.5f, 2.5f, 11.5f }, FacingDirection::FacingNegativeZ, Vector2{ 2.0f, 5.0f }));
	registerObject(new Wall(Vector3{ -1.5f, 2.5f, 12.5f }, FacingDirection::FacingPositiveX, Vector2{ 2.0f, 5.0f }));
	registerObject(new Wall(Vector3{ -3.5f, 2.5f, 12.5f }, FacingDirection::FacingNegativeX, Vector2{ 2.0f, 5.0f }));
	registerObject(new Wall(Vector3{ -2.5f, 2.5f, 13.5f }, FacingDirection::FacingPositiveZ, Vector2{ 2.0f, 5.0f }));


	//  enemies
	Object& enemy_1 = registerObject(new Enemy());

	enemy_1.setPosition(Vector3{ 2.5f, 1.2f,  12.5f });
	



	//  static lights
	globalLight.load(Color::white, Vector3::unitY, 0.4f, 0.0f);
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
