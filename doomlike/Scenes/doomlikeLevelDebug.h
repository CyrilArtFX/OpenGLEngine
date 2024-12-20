#pragma once
#include <Core/scene.h>
#include <GameLogic/playerSpawnPoint.h>

#include <Assets/assetManager.h>
#include <Objects/object.h>

#include <Actors/movingPlatform.h>
#include <Actors/enemy.h>
#include <LevelUtilities/triggerZone.h>

#include <Maths/vector3.h>
#include <Utils/color.h>

#include <Objects/Lights/directionalLight.h>
#include <Objects/Lights/pointLight.h>
#include <Objects/Lights/spotLight.h>


class DoomlikeLevelDebug : public Scene, public PlayerSpawnPoint
{
public:
	DoomlikeLevelDebug();

	void updateScene(float dt) override;


protected:
	void loadScene() override;

	void unloadScene() override;


private:
	//  scene objects
	Object crate1;
	Object crate2;
	Object crate3;
	Object crate4;
	Object crate5;
	Object stair1;
	Object stair2;

	MovingPlatform movingPlatform1;
	MovingPlatform movingPlatform2;
	MovingPlatform movingPlatform3;

	TriggerZone triggerZone1;

	DirectionalLight dirLight;
	PointLight pointLight1;
};

