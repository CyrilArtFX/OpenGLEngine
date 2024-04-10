#pragma once
#include <Events/observer.h>
#include <Core/scene.h>
#include <GameLogic/playerSpawnPoint.h>

#include <Objects/object.h>
#include <Objects/Lights/directionalLight.h>

#include <Decor/wall.h>
#include <Decor/floorceiling.h>
#include <Decor/stairs.h>
#include <Decor/lamps.h>
#include <Actors/enemy.h>
#include <LevelUtilities/enemyCount.h>


class DoomlikeLevelStart : public Scene, public Observer, public PlayerSpawnPoint
{
public:
	DoomlikeLevelStart();

	void updateScene(float dt) override;


protected:
	void loadScene() override;

	void unloadScene() override;


private:
	//  static lights
	DirectionalLight globalLight;

	//  level utilities
	EnemyCount enemyCount;

	Object* endLevelWall;

	void onEnemiesDead();
};

