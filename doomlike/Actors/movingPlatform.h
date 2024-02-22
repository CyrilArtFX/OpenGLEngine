#pragma once
#include <Objects/object.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>

class MovingPlatform : public Object
{
public:
	void load() override;

	void setup(Vector3 pointA_, Vector3 pointB_, float timeAtoB_);
	void updateObject(float dt) override;

private:
	RigidbodyComponent* rigidbody{ nullptr };

	Vector3 pointA{ Vector3::zero };
	Vector3 pointB{ Vector3::zero };
	float timeAtoB{ 0.0f };

	float timer{ 0.0f };
	bool reverse{ false };
	float distance{ 0.0f };
};