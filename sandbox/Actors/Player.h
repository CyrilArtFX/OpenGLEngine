#pragma once

#include <Rendering/camera.h>
#include <Objects/transform.h>

#include "bullet.h"

#include <vector>
#include <GLFW/glfw3.h>


class Player
{
public:
	Player(float height, float speed, std::weak_ptr<class Renderer> renderer, std::weak_ptr<class Model> bulletModel_);

	void update(float dt);

	void unload();

	void processInputs(GLFWwindow* glWindow, float dt);
	void processMouse(float xOffset, float yOffset);
	void processScroll(float scrollOffset);


	std::weak_ptr<Camera> getCamera() { return camera; }

private:
	std::shared_ptr<Camera> camera;
	Transform transform;

	std::weak_ptr<class Renderer> rendererWeak;
	std::shared_ptr<class Model> bulletModel;

	float camHeight;
	float moveSpeed;

	//  fake jump
	float fakeGravity{ -9.0f };
	float height{ 0.0f };
	float jumpVelocity{ 0.0f };

	//  fake shots
	std::vector<std::unique_ptr<Bullet>> bullets;
	float cooldown{ 0.7f };
	float inCooldown{ 0.0f };
	float shootVelocity{ 15.0f };
	float bulletLifeTime{ 5.0f };
};

