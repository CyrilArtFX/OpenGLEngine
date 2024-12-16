#include "doomlikeLevelStart.h"
#include <doomlikeGame.h>
#include <GameplayStatics/gameplayStatics.h>

#include <Assets/assetManager.h>
#include <ServiceLocator/locator.h>

#include <Maths/vector3.h>
#include <Utils/Color.h>

#include <Physics/AABB/boxAABBColComp.h>
#include <iostream>


using Wall::WallObj;
using Stairs::StairsObj;


DoomlikeLevelStart::DoomlikeLevelStart()
{
}

void DoomlikeLevelStart::loadScene()
{
	Renderer& renderer = Locator::getRenderer();

	renderer.SetClearColor(Color{ 50, 75, 75, 255 });

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
	registerObject(new WallObj(Vector3{ 7.5f, 2.5f, 15.0f }, Wall::FacingDirection::FacingNegativeX, Vector2{ 15.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ -5.0f, 2.5f, 22.5f }, Wall::FacingDirection::FacingNegativeZ, Vector2{ 25.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ -7.5f, 2.5f, 12.25f }, Wall::FacingDirection::FacingPositiveX, Vector2{ 9.5f, 5.0f }));

	registerObject(new WallObj(Vector3{ -2.5f, 2.5f, 11.5f }, Wall::FacingDirection::FacingNegativeZ, Vector2{ 2.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ -1.5f, 2.5f, 12.5f }, Wall::FacingDirection::FacingPositiveX, Vector2{ 2.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ -3.5f, 2.5f, 12.5f }, Wall::FacingDirection::FacingNegativeX, Vector2{ 2.0f, 5.0f }));
	registerObject(new WallObj(Vector3{ -2.5f, 2.5f, 13.5f }, Wall::FacingDirection::FacingPositiveZ, Vector2{ 2.0f, 5.0f }));

	registerObject(new StairsObj(Vector3{ 3.8f, 0.0f, 16.0f }, Stairs::FacingDirection::FacingNegativeZ));
	registerObject(new FloorObj(Vector3{ -5.0f, 2.0f, 19.75f }, true)).setScale(Vector3{ 25.0f, 1.0f, 5.5f });
	registerObject(new WallObj(Vector3{ 0.0f, 1.0f, 17.0f }, Wall::FacingDirection::FacingNegativeZ, Vector2{ 15.0f, 2.0f }));
	registerObject(new WallObj(Vector3{ -12.5f, 3.5f, 17.0f }, Wall::FacingDirection::FacingPositiveZ, Vector2{ 10.0f, 3.0f }));
	registerObject(new Ceiling(Vector3{ -12.5f, 5.0f, 19.75f })).setScale(Vector3{ 10.0f, 1.0f, 5.5f });

	endLevelWall = &registerObject(new WallObj(Vector3{ -7.5f, 3.5f, 19.75f }, Wall::FacingDirection::FacingPositiveX, Vector2{5.5f, 3.0f}));


	//  decor
	registerObject(new Lamp(Vector3{ -3.2f, 0.0f, 8.3f }, false, *this, 0.1f));
	registerObject(new Lamp(Vector3{ 3.2f, 0.0f, 8.3f }, false, *this, 0.35f));
	registerObject(new Lamp(Vector3{ 6.5f, 2.0f, 21.5f }, false, *this, 0.67f));
	registerObject(new Lamp(Vector3{ -3.0f, 5.0f, 16.5f }, false, *this, 0.52f));


	//  enemies
	Enemy& enemy_1 = static_cast<Enemy&>(registerObject(new Enemy()));
	Enemy& enemy_2 = static_cast<Enemy&>(registerObject(new Enemy()));

	enemy_1.setPosition(Vector3{ 3.5f, 1.2f,  11.5f });
	enemy_2.setPosition(Vector3{ -3.0f, 3.2f, 20.0f });

	enemyCount.addEnemies({ &enemy_1, &enemy_2 });
	enemyCount.onAllEnemiesDead.registerObserver(this, Bind_0(&DoomlikeLevelStart::onEnemiesDead));


	//  trigger zone
	endLevelZone.setup(Vector3{ -15.0f, 3.5f, 19.75f }, Vector3{ 4.0f, 2.5f, 4.8f });
	endLevelZone.onPlayerEnter.registerObserver(this, Bind_0(&DoomlikeLevelStart::onPlayerEnterEndLevelZone));
	



	//  static lights
	globalLight.load(Color{ 255, 238, 209, 255 }, Vector3::unitY, 0.35f, 0.0f);
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
	endLevelWall->setPosition(Vector3{ -17.5f, 3.5f, 19.75f });
}

void DoomlikeLevelStart::onPlayerEnterEndLevelZone()
{
	std::cout << "Player exit intro level.\n";
	static_cast<DoomlikeGame*>(GameplayStatics::GetGame())->changeLevel(3);
	endLevelZone.onPlayerEnter.unregisterObserver(this);
}
