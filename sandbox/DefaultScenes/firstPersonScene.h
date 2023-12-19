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


class FirstPersonScene : public Scene
{
public:
	FirstPersonScene();

	void load(std::weak_ptr<Renderer> renderer_) override;
	void unload() override;

	void update(float dt) override;


private:
	//  player
	std::unique_ptr<Player> player;


	//  scene objects
	//-----------------

	Object crate1;
	Object crate2;
	Object crate3;
	Object ground;
	Object testMesh;

	DirectionalLight dirLight;
};

