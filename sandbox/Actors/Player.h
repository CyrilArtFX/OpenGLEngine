#pragma once
#include "bullet.h"

#include <Rendering/camera.h>
#include <Objects/transform.h>

#include <vector>


class Player : public Transform
{
public:
	Player(float height, float speed, std::weak_ptr<class Renderer> renderer);

	void update(float dt);

	void unload();


	std::weak_ptr<Camera> getCamera() { return camera; }

private:
	std::shared_ptr<Camera> camera;

	std::weak_ptr<class Renderer> rendererWeak;

	float camHeight;
	float moveSpeed;

	//  fake jump
	float fakeGravity{ -9.0f };
	float height{ 0.0f };
	float jumpVelocity{ 0.0f };

	//  fake shots
	std::vector<std::unique_ptr<Bullet>> bullets;
	float shootVelocity{ 15.0f };
	float bulletLifeTime{ 5.0f };
};

