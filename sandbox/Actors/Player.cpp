#include "Player.h"
#include <Maths/maths.h>
#include <iostream>
#include <algorithm>

Player::Player(float height, float speed, std::weak_ptr<class Renderer> renderer, std::weak_ptr<class Material> bulletMat) : camHeight(height), moveSpeed(speed), rendererWeak(renderer), bulletMaterial(bulletMat.lock())
{
	transform.setPosition(0.0f, 0.0f, 0.0f);
	camera = std::make_shared<Camera>(Vector3{ 0.0f, camHeight, 0.0f });
	camera->setSensitivity(0.08f);
}


void Player::update(float dt)
{
	camera->setPosition(transform.getPosition() + Vector3{0.0f, camHeight, 0.0f});


	//  fake jump
	height = Maths::max(height + (jumpVelocity + fakeGravity) * dt, 0.0f);
	transform.setPosition(transform.getPosition().x, height, transform.getPosition().z);

	jumpVelocity *= 0.95f; //  should scale that by dt but don't know how lol
	if (jumpVelocity < 0.1f || height == 0.0f)
	{
		jumpVelocity = 0.0f;
	}


	//  fake shoot
	inCooldown -= dt;

	for (auto& bullet : bullets)
	{
		bullet->update(dt);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isLTOver())
		{
			bullets[i]->destroy();

			auto iter = std::find(bullets.begin(), bullets.end(), bullets[i]);
			if (iter != bullets.end())
			{
				std::iter_swap(iter, bullets.end() - 1);
				bullets.pop_back();
			}

			i = 0;
		}
	}
}

void Player::unload()
{
	for (auto& bullet : bullets)
	{
		bullet->destroy();
	}
}

void Player::processInputs(GLFWwindow* glWindow, float dt)
{
	//  move camera
	if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS)
		transform.setPosition(transform.getPosition() + camera->getFlatFront() * dt * moveSpeed);

	if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS)
		transform.setPosition(transform.getPosition() + -camera->getFlatFront() * dt * moveSpeed);

	if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS)
		transform.setPosition(transform.getPosition() + camera->getRight() * dt * moveSpeed);

	if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS)
		transform.setPosition(transform.getPosition() + -camera->getRight() * dt * moveSpeed);

	//  fake jump
	if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_PRESS && height == 0.0f)
		jumpVelocity = 40.0f;

	//  fake shoot
	if (glfwGetKey(glWindow, GLFW_KEY_Q) == GLFW_PRESS && inCooldown <= 0.0f)
	{
		bullets.push_back(std::make_unique<Bullet>(camera->getPosition(), camera->getForward(), shootVelocity, bulletLifeTime, rendererWeak, bulletMaterial));
		inCooldown = cooldown;
	}
}

void Player::processMouse(float xOffset, float yOffset)
{
	camera->freecamMouseMovement(xOffset, yOffset);
}

void Player::processScroll(float scrollOffset)
{
}