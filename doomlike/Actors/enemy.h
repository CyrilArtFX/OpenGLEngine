#pragma once
#include <Objects/object.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>
#include <Events/observer.h>

class Player;

class Enemy : public Object, public Observer
{
public:
	void load() override;

	void update(float dt);

private:
	void onBodyIntersect(RigidbodyComponent& other);

	RigidbodyComponent* rigidbody{ nullptr };

	Player* playerRef{ nullptr };

	float range{ 9.0f };
};