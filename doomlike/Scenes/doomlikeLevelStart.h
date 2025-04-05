#pragma once
#include <Core/scene.h>
#include <Events/observer.h>
#include <GameLogic/playerSpawnPoint.h>

//#include <LevelUtilities/enemyCount.h>
//#include <LevelUtilities/triggerZone.h>


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
	//TriggerZone endLevelZone;

	Entity* endLevelWall;

	void onEnemiesDead();
	void onPlayerEnterEndLevelZone();
};

