#pragma once
#include <Core/scene.h>
#include <GameLogic/playerSpawnPoint.h>

#include <Assets/assetManager.h>
#include <Objects/object.h>

#include <Maths/vector3.h>
#include <Utils/color.h>

#include <Objects/Lights/directionalLight.h>
#include <Objects/Lights/pointLight.h>
#include <Objects/Lights/spotLight.h>


class DoomlikeLevelOne : public Scene, public PlayerSpawnPoint
{
public:
	DoomlikeLevelOne();

	void update(float dt) override;


protected:
	void loadScene() override;

	void unloadScene() override;


private:
	//  scene objects
	Object ground1;
	Object ground2;
	Object ground3;
	Object crate1;
	Object crate2;
	Object crate3;
	Object crate4;
	Object stair1;
	Object stair2;

	DirectionalLight dirLight;
	PointLight pointLight1;
};

