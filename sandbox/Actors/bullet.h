#pragma once
#include <Maths/vector3.h>
#include <Rendering/Model/vertexArray.h>
#include <Objects/object.h>
#include <Rendering/material.h>

class Bullet
{
public:
	Bullet(Vector3 spawnPos, Quaternion spawnRot, Vector3 direction_, float velocity_, float lifetime_, std::weak_ptr<class Renderer> renderer_);
	Bullet() = delete;
	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;

	void destroy();

	void update(float dt);

	bool isLTOver() { return lifetime <= 0.0f; }

private:
	Vector3 direction;
	float velocity;
	float lifetime;
	std::shared_ptr<class Renderer> renderer;

	std::shared_ptr<Object> object;
};

