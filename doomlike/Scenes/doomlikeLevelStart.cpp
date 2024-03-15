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
	registerObject(new FloorObj(Vector3{0.0f, 0.0f,  2.5f})).setScale(Vector3{ 5.0f, 1.0f, 10.0f});
	registerObject(new FloorObj(Vector3{0.0f, 0.0f, 15.0f})).setScale(Vector3{15.0f, 1.0f, 15.0f});
	registerObject(new Ceiling(Vector3{0.0f, 3.0f,  2.5f})).setScale(Vector3{ 5.0f, 1.0f, 10.0f});
	registerObject(new Ceiling(Vector3{0.0f, 5.0f, 15.0f})).setScale(Vector3{15.0f, 1.0f, 15.0f});

	registerObject(new Wall(Vector3{ 0.0f, 1.5f, -2.5f }, FacingDirection::FacingPositiveZ)).setScale(Vector3{ 5.0f, 1.0f, 3.0f });
	registerObject(new Wall(Vector3{ -2.5f, 1.5f, 2.5f }, FacingDirection::FacingPositiveX)).setScale(Vector3{ 10.0f, 1.0f, 3.0f });
	registerObject(new Wall(Vector3{  2.5f, 1.5f, 2.5f }, FacingDirection::FacingNegativeX)).setScale(Vector3{ 10.0f, 1.0f, 3.0f });

	/*
	registerObject(new FloorObj(Vector3{  0.0f, 0.0f,  0.0f }));
	registerObject(new FloorObj(Vector3{  5.0f, 0.0f,  0.0f }));
	registerObject(new FloorObj(Vector3{ 10.0f, 0.0f, -5.0f }));
	registerObject(new FloorObj(Vector3{ 10.0f, 0.0f,  0.0f }));
	registerObject(new FloorObj(Vector3{ 10.0f, 0.0f,  5.0f }));
	registerObject(new FloorObj(Vector3{ 15.0f, 0.0f, -5.0f }));
	registerObject(new FloorObj(Vector3{ 15.0f, 0.0f,  0.0f }));
	registerObject(new FloorObj(Vector3{ 15.0f, 0.0f,  5.0f }));
	registerObject(new FloorObj(Vector3{ 20.0f, 0.0f, -5.0f }));
	registerObject(new FloorObj(Vector3{ 20.0f, 0.0f,  0.0f }));
	registerObject(new FloorObj(Vector3{ 20.0f, 0.0f,  5.0f }));
	
	registerObject(new Ceiling(Vector3{  0.0f, 2.5f,  0.0f }));
	registerObject(new Ceiling(Vector3{  5.0f, 2.5f,  0.0f }));
	registerObject(new Ceiling(Vector3{ 10.0f, 5.0f, -5.0f }));
	registerObject(new Ceiling(Vector3{ 10.0f, 5.0f,  0.0f }));
	registerObject(new Ceiling(Vector3{ 10.0f, 5.0f,  5.0f }));
	registerObject(new Ceiling(Vector3{ 15.0f, 5.0f, -5.0f }));
	registerObject(new Ceiling(Vector3{ 15.0f, 5.0f,  0.0f }));
	registerObject(new Ceiling(Vector3{ 15.0f, 5.0f,  5.0f }));
	registerObject(new Ceiling(Vector3{ 20.0f, 5.0f, -5.0f }));
	registerObject(new Ceiling(Vector3{ 20.0f, 5.0f,  0.0f }));
	registerObject(new Ceiling(Vector3{ 20.0f, 5.0f,  5.0f })); 
	
	registerObject(new Wall(Vector3{ -2.5f, 2.5f, 0.0f }, FacingDirection::FacingPositiveX, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 0.0f, 2.5f, -2.5f }, FacingDirection::FacingPositiveZ, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 5.0f, 2.5f, -2.5f }, FacingDirection::FacingPositiveZ, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 0.0f, 2.5f,  2.5f }, FacingDirection::FacingNegativeZ, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 5.0f, 2.5f,  2.5f }, FacingDirection::FacingNegativeZ, WallSize::WallBig));

	registerObject(new Wall(Vector3{  7.5f, 2.5f, -5.0f }, FacingDirection::FacingPositiveX, WallSize::WallBig));
	registerObject(new Wall(Vector3{  7.5f, 5.0f,  0.0f }, FacingDirection::FacingPositiveX, WallSize::WallBig));
	registerObject(new Wall(Vector3{  7.5f, 2.5f,  5.0f }, FacingDirection::FacingPositiveX, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 10.0f, 2.5f, -7.5f }, FacingDirection::FacingPositiveZ, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 15.0f, 2.5f, -7.5f }, FacingDirection::FacingPositiveZ, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 20.0f, 2.5f, -7.5f }, FacingDirection::FacingPositiveZ, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 10.0f, 2.5f,  7.5f }, FacingDirection::FacingNegativeZ, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 15.0f, 2.5f,  7.5f }, FacingDirection::FacingNegativeZ, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 20.0f, 2.5f,  7.5f }, FacingDirection::FacingNegativeZ, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 22.5f, 2.5f, -5.0f }, FacingDirection::FacingNegativeX, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 22.5f, 2.5f,  0.0f }, FacingDirection::FacingNegativeX, WallSize::WallBig));
	registerObject(new Wall(Vector3{ 22.5f, 2.5f,  5.0f }, FacingDirection::FacingNegativeX, WallSize::WallBig));

	registerObject(new Wall(Vector3{ 11.25f, 1.25f,  2.5f }, FacingDirection::FacingNegativeX, WallSize::WallSmall));
	registerObject(new Wall(Vector3{ 11.25f, 3.75f,  2.5f }, FacingDirection::FacingNegativeX, WallSize::WallSmall));
	registerObject(new Wall(Vector3{  12.5f, 1.25f, 1.25f }, FacingDirection::FacingNegativeZ, WallSize::WallSmall));
	registerObject(new Wall(Vector3{  12.5f, 3.75f, 1.25f }, FacingDirection::FacingNegativeZ, WallSize::WallSmall));
	registerObject(new Wall(Vector3{  12.5f, 1.25f, 3.75f }, FacingDirection::FacingPositiveZ, WallSize::WallSmall));
	registerObject(new Wall(Vector3{  12.5f, 3.75f, 3.75f }, FacingDirection::FacingPositiveZ, WallSize::WallSmall));
	registerObject(new Wall(Vector3{ 13.75f, 1.25f,  2.5f }, FacingDirection::FacingPositiveX, WallSize::WallSmall));
	registerObject(new Wall(Vector3{ 13.75f, 3.75f,  2.5f }, FacingDirection::FacingPositiveX, WallSize::WallSmall));

	registerObject(new Wall(Vector3{ 16.25f, 1.25f,  -2.5f }, FacingDirection::FacingNegativeX, WallSize::WallSmall));
	registerObject(new Wall(Vector3{ 16.25f, 3.75f,  -2.5f }, FacingDirection::FacingNegativeX, WallSize::WallSmall));
	registerObject(new Wall(Vector3{  17.5f, 1.25f, -3.75f }, FacingDirection::FacingNegativeZ, WallSize::WallSmall));
	registerObject(new Wall(Vector3{  17.5f, 3.75f, -3.75f }, FacingDirection::FacingNegativeZ, WallSize::WallSmall));
	registerObject(new Wall(Vector3{  17.5f, 1.25f, -1.25f }, FacingDirection::FacingPositiveZ, WallSize::WallSmall));
	registerObject(new Wall(Vector3{  17.5f, 3.75f, -1.25f }, FacingDirection::FacingPositiveZ, WallSize::WallSmall));
	registerObject(new Wall(Vector3{ 18.75f, 1.25f,  -2.5f }, FacingDirection::FacingPositiveX, WallSize::WallSmall));
	registerObject(new Wall(Vector3{ 18.75f, 3.75f,  -2.5f }, FacingDirection::FacingPositiveX, WallSize::WallSmall));


	//  enemies
	Object& enemy_1 = registerObject(new Enemy());
	Object& enemy_2 = registerObject(new Enemy());

	enemy_1.setPosition(Vector3{ 17.5f, 1.2f,  2.5f });
	enemy_2.setPosition(Vector3{ 12.5f, 1.2f, -2.5f });
	*/



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
