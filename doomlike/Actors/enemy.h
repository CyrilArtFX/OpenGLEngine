#pragma once
#include <Objects/object.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>

#include <Events/event.h>
#include <Events/observer.h>

class Player;

class Enemy : public Object, public Observer
{
public:
	void load() override;

	void updateObject(float dt) override;

	Event<Enemy*> onDie;

private:
	void onBodyIntersect(RigidbodyComponent& other);

	RigidbodyComponent* rigidbody{ nullptr };

	Player* playerRef{ nullptr };

	float range{ 9.0f };
	float speed{ 2.0f };
	bool dead{ false };
};