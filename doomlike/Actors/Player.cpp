#include "Player.h"

#include <Inputs/input.h>
#include <Maths/maths.h>
#include <Physics/physics.h>

#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>


Player::Player()
{
}

void Player::setup(float height, float speed, Renderer* renderer)
{
	camHeight = height;
	moveSpeed = speed;
	rendererRef = renderer;

	setPosition(0.0f, 0.0f, 0.0f);
	camera.setPosition(Vector3{ 0.0f, camHeight, 0.0f });
	camera.setSensitivity(0.08f);
}


void Player::update(float dt)
{
	//  move camera
	if (Input::IsKeyDown(GLFW_KEY_W))
		setPosition(getPosition() + camera.getFlatFront() * dt * moveSpeed);

	if (Input::IsKeyDown(GLFW_KEY_S))
		setPosition(getPosition() + -camera.getFlatFront() * dt * moveSpeed);

	if (Input::IsKeyDown(GLFW_KEY_A))
		setPosition(getPosition() + camera.getRight() * dt * moveSpeed);

	if (Input::IsKeyDown(GLFW_KEY_D))
		setPosition(getPosition() + -camera.getRight() * dt * moveSpeed);

	//  fake jump
	if (Input::IsKeyPressed(GLFW_KEY_SPACE) && height == 0.0f)
		jumpVelocity = 40.0f;

	//  fake shoot
	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		if (rendererRef)
		{
			Quaternion bullet_rotation = camera.getRotation();
			bullet_rotation = Quaternion::concatenate(bullet_rotation, Quaternion{ camera.getUp(), Maths::toRadians(90.0f) });
			bullets.push_back(std::make_unique<Bullet>(camera.getPosition(), bullet_rotation, camera.getForward(), shootVelocity, bulletLifeTime, rendererRef));
		}
		else
		{
			std::cout << "Doomlike game error : Player has not his renderer ref setup !\n";
		}
	}

	//  shoot raycast
	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		Vector3 raycast_start = camera.getPosition();
		Vector3 raycast_end = raycast_start + camera.getForward() * 5.0f;

		Physics::RaycastLine(raycast_start, raycast_end);
	}


	Vector2 mouse_delta = Input::GetMouseDelta(); 
	camera.freecamMouseMovement(mouse_delta.x, mouse_delta.y); 

	camera.setPosition(getPosition() + Vector3{0.0f, camHeight, 0.0f});


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

			std::iter_swap(bullets.begin() + i, bullets.end() - 1);
			bullets.pop_back();

			break; //  assume that we can't create 2 bullets on the same frame
		}
	}
}

void Player::unload()
{
	for (auto& bullet : bullets)
	{
		bullet->destroy();
	}
	bullets.clear();
}

void Player::respawn(PlayerSpawnPoint& spawnPoint)
{
	unload();

	setPosition(spawnPoint.spawnPosition);
	//setRotation(spawnPoint.spawnRotation);

	camera.setPosition(spawnPoint.spawnPosition + Vector3{ 0.0f, camHeight, 0.0f });
	//camera.setRotByQuaternion(spawnPoint.spawnRotation);
}
