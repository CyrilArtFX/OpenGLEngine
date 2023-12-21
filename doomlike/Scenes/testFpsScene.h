#pragma once
#include <Core/scene.h>

#include <Assets/assetManager.h>
#include <Objects/object.h>

#include <Actors/player.h>

#include <Maths/vector3.h>
#include <Utils/color.h>

#include <Objects/Lights/directionalLight.h>
#include <Objects/Lights/pointLight.h>
#include <Objects/Lights/spotLight.h>


class TestFpsScene : public Scene
{
public:
	TestFpsScene();

	void unloadScene() override;

	void update(float dt) override;


protected:
	void loadScene() override;


private:
	//  player
	Player player;


	//  scene objects
	//-----------------

	Object crate1;
	Object crate2;
	Object crate3;
	Object ground;
	Object testMesh;

	DirectionalLight dirLight;
};

