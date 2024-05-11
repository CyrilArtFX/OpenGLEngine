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
#include <Actors/movingPlatform.h>
#include <Actors/enemy.h>

#include <LevelUtilities/triggerZone.h>


class DoomlikeLevelAdvanced : public Scene, public Observer, public PlayerSpawnPoint
{
public:
	DoomlikeLevelAdvanced();

	void updateScene(float dt) override;


protected:
	void loadScene() override;

	void unloadScene() override;


private:
	//  static lights
	DirectionalLight globalLight;

	//  dynamic lights
	Lamp* ceilLamp1;
	Lamp* ceilLamp2;
	Lamp* ceilLamp3;
	Lamp* ceilLamp4;
	Lamp* ceilLamp5;
	Lamp* ceilLamp6;
	Lamp* ceilLamp7;
	Lamp* ceilLamp8;
	Lamp* floorLamp;

	//  level utilities
	TriggerZone elevatorUpZone;
	TriggerZone enemySpawnZone;

	//  objects
	MovingPlatform elevator;
	float elevatorTimer{ 0.0f };

	void onPlayerEnterElevatorUpZone();
	void onPlayerEnterEnemySpawnZone();
};

