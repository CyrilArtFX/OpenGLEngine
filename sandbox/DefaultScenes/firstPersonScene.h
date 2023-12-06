#pragma once
#include <Core/scene.h>

#include <Rendering/shader.h>
#include <Rendering/texture.h>
#include <Rendering/material.h>

#include <Rendering/Model/Mesh.h>
#include <Rendering/Model/Model.h>
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

	void processInputs(GLFWwindow* glWindow, float dt) override;
	void processMouse(float xOffset, float yOffset) override;
	void processScroll(float scrollOffset) override;


private:
	//  player
	std::unique_ptr<Player> player;


	//  scene objects
	//-----------------

	std::shared_ptr<Shader> litObjectShader;
	std::shared_ptr<Shader> bulletShader;

	std::shared_ptr<Mesh> meshCube;
	std::shared_ptr<Mesh> meshPlane;

	std::shared_ptr<Model> modelCrate;
	std::shared_ptr<Model> modelGround;
	std::shared_ptr<Model> modelBullet;

	std::shared_ptr<Material> crateMat;
	std::shared_ptr<Material> groundMat;

	std::shared_ptr<Object> crate1;
	std::shared_ptr<Object> crate2;
	std::shared_ptr<Object> crate3;
	std::shared_ptr<Object> ground;
};

