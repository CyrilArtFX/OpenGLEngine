#include "Player.h"
#include <Maths/maths.h>

Player::Player(float height, float speed, std::weak_ptr<Material> materialToUse) : camHeight(height), moveSpeed(speed)
{
	float blank_vertices[] = { 0.0f };
	vaBlank = std::make_shared<VertexArray>(blank_vertices, 0);
	blankObject = std::make_unique<Object>(materialToUse, vaBlank);

	camera = std::make_shared<Camera>(Vector3{ 0.0f, height, 0.0f });
	camera->setSensitivity(0.08f);
}


void Player::update(float dt)
{
	camera->setPosition(blankObject->getPosition() + Vector3{ 0.0f, camHeight, 0.0f });


	//  fake jump
	height = Maths::max(height + (jumpVelocity + fakeGravity) * dt, 0.0f);
	blankObject->setPosition(blankObject->getPosition().x, height, blankObject->getPosition().z);

	jumpVelocity *= 0.9f;
	if (jumpVelocity < 0.1f || height == 0.0f)
	{
		jumpVelocity = 0.0f;
	}
}

void Player::processInputs(GLFWwindow* glWindow, float dt)
{
	//  move camera
	if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS)
		blankObject->setPosition(blankObject->getPosition() + camera->getFlatFront() * dt * moveSpeed);

	if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS)
		blankObject->setPosition(blankObject->getPosition() + -camera->getFlatFront() * dt * moveSpeed); 

	if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS)
		blankObject->setPosition(blankObject->getPosition() + camera->getRight() * dt * moveSpeed);

	if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS)
		blankObject->setPosition(blankObject->getPosition() + -camera->getRight() * dt * moveSpeed);

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


void Player::unload()
{
	blankObject->deleteObject();
	vaBlank->deleteObjects();
}