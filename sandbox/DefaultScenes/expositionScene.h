#pragma once
#include <Core/scene.h>

#include <Rendering/shader.h>
#include <Rendering/texture.h>
#include <Rendering/material.h>

#include <Rendering/Model/Mesh.h>
#include <Rendering/Model/Model.h>
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

	std::shared_ptr<Shader> litObjectShader;
	std::shared_ptr<Shader> flatEmissiveShader;

	std::shared_ptr<Mesh> meshCube;
	std::shared_ptr<Model> modelContainer;
	std::shared_ptr<Model> modelLightCube;

	std::shared_ptr<Material> containerMat;
	std::shared_ptr<Material> lightSourceMat;

	std::shared_ptr<Object> cube1;
	std::shared_ptr<Object> cube2;
	std::shared_ptr<Object> cube3;
	std::shared_ptr<Object> lightCube1;
	std::shared_ptr<Object> lightCube2;

	std::shared_ptr<SpotLight> flashLight;
};

