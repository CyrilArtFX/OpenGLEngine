#include "Player.h"

#include <Inputs/input.h>
#include <Maths/maths.h>

#include <GLFW/glfw3.h>
#include <algorithm>


Player::Player(float height, float speed, std::weak_ptr<class Renderer> renderer) : camHeight(height), moveSpeed(speed), rendererWeak(renderer)
{
	setPosition(0.0f, 0.0f, 0.0f);
	camera = std::make_shared<Camera>(Vector3{ 0.0f, camHeight, 0.0f });
	camera->setSensitivity(0.08f);
}


void Player::update(float dt)
{
	//  move camera
	if (Input::IsKeyDown(GLFW_KEY_W))
		setPosition(getPosition() + camera->getFlatFront() * dt * moveSpeed);

	if (Input::IsKeyDown(GLFW_KEY_S))
		setPosition(getPosition() + -camera->getFlatFront() * dt * moveSpeed);

	if (Input::IsKeyDown(GLFW_KEY_A))
		setPosition(getPosition() + camera->getRight() * dt * moveSpeed);

	if (Input::IsKeyDown(GLFW_KEY_D))
		setPosition(getPosition() + -camera->getRight() * dt * moveSpeed);

	//  fake jump
	if (Input::IsKeyPressed(GLFW_KEY_SPACE) && height == 0.0f)
		jumpVelocity = 40.0f;

	//  fake shoot
	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		Quaternion bullet_rotation = camera->getRotation();
		bullet_rotation = Quaternion::concatenate(bullet_rotation, Quaternion{ camera->getUp(), Maths::toRadians(90.0f) });
		bullets.push_back(std::make_unique<Bullet>(camera->getPosition(), bullet_rotation, camera->getForward(), shootVelocity, bulletLifeTime, rendererWeak));
	}

	Vector2 mouse_delta = Input::GetMouseDelta(); 
	camera->freecamMouseMovement(mouse_delta.x, mouse_delta.y); 



	camera->setPosition(getPosition() + Vector3{0.0f, camHeight, 0.0f});


	//  fake jump
	height = Maths::max(height + (jumpVelocity + fakeGravity) * dt, 0.0f);
	setPosition(getPosition().x, height, getPosition().z);

	jumpVelocity *= 0.95f; //  should scale that by dt but don't know how lol
	if (jumpVelocity < 0.1f || height == 0.0f)
	{
		jumpVelocity = 0.0f;
	}


	//  fake shoot
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