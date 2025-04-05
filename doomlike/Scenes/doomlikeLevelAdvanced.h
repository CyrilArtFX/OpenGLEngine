#pragma once
#include <Core/scene.h>
#include <Events/observer.h>
#include <GameLogic/playerSpawnPoint.h>

//#include <Actors/movingPlatform.h>
//#include <LevelUtilities/triggerZone.h>


class DoomlikeLevelAdvanced : public Scene, public Observer, public PlayerSpawnPoint
{
public:
	void updateScene(float dt) override;


protected:
	void loadScene() override;
	void unloadScene() override;


private:
	//  dynamic lights
	Entity* ceilLamp1;
	Entity* ceilLamp2;
	Entity* ceilLamp3;
	Entity* ceilLamp4;
	Entity* ceilLamp5;
	Entity* ceilLamp6;
	Entity* ceilLamp7;
	Entity* ceilLamp8;
	Entity* floorLamp;

	//  level utilities
	//TriggerZone elevatorUpZone;
	//TriggerZone enemySpawnZone;

	//MovingPlatform elevator;
	float elevatorTimer{ 0.0f };

	void onPlayerEnterElevatorUpZone();
	void onPlayerEnterEnemySpawnZone();
};

