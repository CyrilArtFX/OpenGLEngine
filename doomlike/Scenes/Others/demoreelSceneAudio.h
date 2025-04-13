#pragma once
#include <Core/scene.h>
#include <GameLogic/playerSpawnPoint.h>

class DemoreelSceneAudio : public Scene, public PlayerSpawnPoint
{
protected:
	void loadScene() override;
	void unloadScene() override;
};

