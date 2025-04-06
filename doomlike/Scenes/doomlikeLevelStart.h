#pragma once
#include <Core/scene.h>
#include <Events/observer.h>
#include <GameLogic/playerSpawnPoint.h>

//#include <LevelUtilities/enemyCount.h>


class DoomlikeLevelStart : public Scene, public Observer, public PlayerSpawnPoint
{
public:
	void updateScene(float dt) override;


protected:
	void loadScene() override;
	void unloadScene() override;


private:
	//  level utilities
	//EnemyCount enemyCount;

	Entity* endLevelWall;
	Entity* endLevelZone;

	void onEnemiesDead();
	void onEnterEndLevelZone(class RigidbodyComponent& other);
};

