#pragma once
#include <Core/scene.h>
#include <GameLogic/playerSpawnPoint.h>


class DoomlikeLevelDebug : public Scene, public PlayerSpawnPoint
{
public:
	void updateScene(float dt) override;

protected:
	void loadScene() override;
	void unloadScene() override;
};

