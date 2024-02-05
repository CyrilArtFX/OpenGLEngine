#pragma once
#include "bullet.h"

#include <Rendering/camera.h>
#include <Objects/transform.h>

#include <GameLogic/playerSpawnPoint.h>

#include <vector>

class Renderer;

class Player : public Transform
{
public:
	Player();
	void setup(float height, float speed, Renderer* renderer);

	void update(float dt);

	void unload();

	//  set rotation to spawn point not working because of camera
	void respawn(PlayerSpawnPoint& spawnPoint);


	Camera& getCamera() { return camera; }

private:
	Camera camera;

	Renderer* rendererRef{ nullptr };

	float camHeight{ 0.0f };
	float moveSpeed{ 0.0f };

	//  fake jump
	float fakeGravity{ -9.0f };
	float height{ 0.0f };
	float jumpVelocity{ 0.0f };

	//  fake shots
	std::vector<std::unique_ptr<Bullet>> bullets;
	float shootVelocity{ 15.0f };
	float bulletLifeTime{ 3.0f };
};

