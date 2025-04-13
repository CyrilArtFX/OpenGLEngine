#pragma once
#include <Core/scene.h>
#include <GameLogic/playerSpawnPoint.h>


class DemoreelScenePhysics : public Scene, public PlayerSpawnPoint
{
protected:
	void loadScene() override;
	void unloadScene() override;
	void updateScene(float dt) override;

	Entity* movingPlatform{ nullptr };
};

