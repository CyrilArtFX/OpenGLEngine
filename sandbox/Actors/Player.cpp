#include "Player.h"
#include <Maths/maths.h>

Player::Player(float height, float speed) : camHeight(height), moveSpeed(speed)
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
		jumpVelocity = 30.0f;
}

void Player::processMouse(float xOffset, float yOffset)
{
	camera->processMouseMovement(xOffset, yOffset);
}

void Player::processScroll(float scrollOffset)
{
}