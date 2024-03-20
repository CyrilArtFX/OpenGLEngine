#include "doomlikeLevelStart.h"

#include <Assets/assetManager.h>
#include <Physics/physics.h>

#include <Maths/vector3.h>
#include <Utils/Color.h>

#include <Physics/AABB/boxAABBColComp.h>


using Wall::WallObj;
using Stairs::StairsObj;


DoomlikeLevelStart::DoomlikeLevelStart()
{
}

void DoomlikeLevelStart::loadScene()
{
	renderer->setClearColor(Color{ 50, 75, 75, 255 });

	//  floors, ceilings, walls and stairs
	registerObject(new FloorObj(Vector3{ 0.0f, 0.0f,  2.5f }, true)).setScale(Vector3{ 5.0f, 1.0f, 10.0f });
	registerObject(new FloorObj(Vector3{ 0.0f, 0.0f, 15.0f }, false)).setScale(Vector3{ 15.0f, 1.0f, 15.0f });
	registerObject(new Ceiling(Vector3{ 0.0f, 3.0f,  2.5f })).setScale(Vector3{ 5.0f, 1.0f, 10.0f });
	registerObject(new Ceiling(Vector3{ 0.0f, 5.0f, 15.0f })).setScale(Vector3{ 15.0f, 1.0f, 15.0f });

	registerObject(new WallObj(Vector3{ 0.0f, 1.5f, -2.5f }, Wall::FacingDirection::FacingPositiveZ, Vector2{ 5.0f, 3.0f }));
	registerObject(new WallObj(Vector3{ -2.5f, 1.5f, 2.5f }, Wall::FacingDirection::FacingPositiveX, Vector2{ 10.0f, 3.0f }));
	registerObject(new WallObj(Vector3{ 2.5f, 1.5f, 2.5f }, Wall::FacingDirection::FacingNegativeX, Vector2{ 10.0f, 3.0f }));

	registerObject(new WallObj(Vector3{ -5.0f, 2.5f, 7.5f }, Wall::FacingDirection::FacingPositiveZ, Vector2{ 5.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ 0.0f, 4.0f, 7.5f }, Wall::FacingDirection::FacingPositiveZ, Vector2{ 5.0f, 2.0f }));
	registerObject(new WallObj(Vector3{ 5.0f, 2.5f, 7.5f }, Wall::FacingDirection::FacingPositiveZ, Vector2{ 5.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ -7.5f, 2.5f, 15.0f }, Wall::FacingDirection::FacingPositiveX, Vector2{ 15.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ 7.5f, 2.5f, 15.0f }, Wall::FacingDirection::FacingNegativeX, Vector2{ 15.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ 0.0f, 2.5f, 22.5f }, Wall::FacingDirection::FacingNegativeZ, Vector2{ 15.0f, 5.0f }));

	registerObject(new WallObj(Vector3{ -2.5f, 2.5f, 11.5f }, Wall::FacingDirection::FacingNegativeZ, Vector2{ 2.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ -1.5f, 2.5f, 12.5f }, Wall::FacingDirection::FacingPositiveX, Vector2{ 2.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ -3.5f, 2.5f, 12.5f }, Wall::FacingDirection::FacingNegativeX, Vector2{ 2.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ -2.5f, 2.5f, 13.5f }, Wall::FacingDirection::FacingPositiveZ, Vector2{ 2.0f, 5.0f }));

	registerObject(new StairsObj(Vector3{ 3.8f, 0.0f, 16.0f }, Stairs::FacingDirection::FacingNegativeZ));
	registerObject(new FloorObj(Vector3{ 0.0f, 2.0f, 19.75f }, true)).setScale(Vector3{ 15.0f, 1.0f, 5.5f });
	registerObject(new WallObj(Vector3{ 0.0f, 1.0f, 17.0f }, Wall::FacingDirection::FacingNegativeZ, Vector2{ 15.0f, 2.0f }));


	//  enemies
	Enemy& enemy_1 = static_cast<Enemy&>(registerObject(new Enemy()));
	Enemy& enemy_2 = static_cast<Enemy&>(registerObject(new Enemy()));

	enemy_1.setPosition(Vector3{ 3.5f, 1.2f,  11.5f });
	enemy_2.setPosition(Vector3{ -3.0f, 3.2f, 20.0f });

	enemyCount.addEnemies({ &enemy_1, &enemy_2 });
	enemyCount.onAllEnemiesDead.registerObserver(this, Bind_0(&DoomlikeLevelStart::onEnemiesDead));
	



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
	enemyCount.clearEnemies(true);
}

void DoomlikeLevelStart::onEnemiesDead()
{
	std::cout << "All enemies of the level are dead!\n";
}
