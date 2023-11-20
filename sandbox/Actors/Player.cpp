#include "Player.h"

Player::Player(float height, std::weak_ptr<Material> materialToUse)
{
	float blank_vertices[] = { 0.0f };
	vaBlank = std::make_shared<VertexArray>(blank_vertices, 0);
	blankObject = std::make_unique<Object>(materialToUse, vaBlank);

	camera = std::make_shared<Camera>(Vector3{ 0.0f, height, 0.0f });
}


void Player::update(float dt)
{
}

void Player::processInputs(GLFWwindow* glWindow, float dt)
{
	//  move camera
	if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(Forward, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(Backward, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(Left, dt);

	if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(Right, dt);
}

void Player::processMouse(float xOffset, float yOffset)
{
}

void Player::processScroll(float scrollOffset)
{
}


void Player::unload()
{
	blankObject->deleteObject();
	vaBlank->deleteObjects();
}