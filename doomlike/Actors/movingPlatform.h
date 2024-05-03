#pragma once
#include <Objects/object.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>

class MovingPlatform : public Object
{
public:
	void load() override;

	void setup(Vector3 pointA_, Vector3 pointB_, float timeAtoB_, float waitTime_ = 0.0f);
	void updateObject(float dt) override;

	void pause();
	void resume();

private:
	RigidbodyComponent* rigidbody{ nullptr };

	Vector3 pointA{ Vector3::zero };
	Vector3 pointB{ Vector3::zero };
	float timeAtoB{ 0.0f };
	float waitTime{ 0.0f };

	float timer{ 0.0f };
	float waitTimer{ 0.0f };
	bool reverse{ false };
	bool waiting{ false };
	bool paused{ false };
	float distance{ 0.0f };
};