#pragma once
#include <Core/scene.h>
#include <GameLogic/playerSpawnPoint.h>

#include <Objects/object.h>

#include <Objects/Lights/directionalLight.h>


class DoomlikeLevelStart : public Scene, public PlayerSpawnPoint
{
public:
	DoomlikeLevelStart();

	void updateScene(float dt) override;


protected:
	void loadScene() override;

	void unloadScene() override;


private:
	//  static scene objects
	Object ground;
	Object wall;
	Object wall2;

	DirectionalLight globalLight;
};

