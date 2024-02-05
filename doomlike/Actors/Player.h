#pragma once
#include "bullet.h"

#include <Rendering/camera.h>
#include <Objects/transform.h>

#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>

#include <GameLogic/playerSpawnPoint.h>

#include <Events/observer.h>

#include <vector>

class Renderer;

class Player : public Transform, public Observer
{
public:
	Player();
	void setup(float height, float speed, Renderer* renderer);

	void update(float dt);

	void unload();

	//  set rotation to spawn point not working because of camera
	void respawn(PlayerSpawnPoint& spawnPoint);


	void onRigidbodyDeleted();


	Camera& getCamera() { return camera; }

private:
	Camera camera;

	Renderer* rendererRef{ nullptr };

	float camHeight{ 0.0f };
	float moveSpeed{ 0.0f };
	bool onGround{ false };

	//  fake shots
	std::vector<std::unique_ptr<Bullet>> bullets;
	float shootVelocity{ 15.0f };
	float bulletLifeTime{ 3.0f };

	RigidbodyComponent* rigidbody;
};

