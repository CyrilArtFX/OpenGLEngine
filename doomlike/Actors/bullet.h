#pragma once
#include <Maths/vector3.h>
#include <Rendering/Model/vertexArray.h>
#include <Objects/object.h>
#include <Rendering/material.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>
#include <Events/observer.h>


class Bullet : private Observer
{
public:
	Bullet(Vector3 spawnPos, Quaternion spawnRot, Vector3 direction_, float velocity_, float lifetime_);

	void destroy();

	void update(float dt);

	bool isLTOver() { return lifetime <= 0.0f; }

	void onBulletWallHit(const CollisionResponse& hitResponse);
	void onBulletEntityHit(RigidbodyComponent& hitBody);
	void onRigidbodyDeleted();

private:
	float lifetime{ 0.0f };

	Object object;

	RigidbodyComponent* rigidbody;
};

