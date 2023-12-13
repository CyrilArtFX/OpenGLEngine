#pragma once
#include <Core/scene.h>

#include <Assets/assetManager.h>
#include <Objects/object.h>

#include <Maths/vector3.h>
#include <Utils/color.h>

#include <Objects/Lights/directionalLight.h>
#include <Objects/Lights/pointLight.h>
#include <Objects/Lights/spotLight.h>


class ExpositionScene : public Scene
{
public:
	ExpositionScene();

	void load(std::weak_ptr<Renderer> renderer_) override;
	void unload() override;

	void update(float dt) override;

	void processInputs(GLFWwindow* glWindow, float dt) override;
	void processMouse(float xOffset, float yOffset) override;
	void processScroll(float scrollOffset) override;

private:
	//  scene objects
	//-----------------

	Object cube1;
	Object cube2;
	Object cube3;
	Object lightCube1;
	Object lightCube2;

	DirectionalLight sunLight;
	PointLight pointLight1;
	PointLight pointLight2;
	SpotLight flashLight;
};

