#pragma once
#include <ECS/component.h>
#include <Events/observer.h>
#include <Events/event.h>


/**
* This component creates an enemy from an entity.
* It automatically creates every needed components.
*/
class EnemyComponent : public Component, public Observer
{
public:
	Event<Entity*> onDie;

protected:
	void init() override;
	void exit() override;
	void update(float deltaTime) override;

private:
	Entity* entity{ nullptr };
	std::shared_ptr<class ModelRendererComponent> enemyModel;
	std::shared_ptr<class BoxAABBColComp> collision;
	std::shared_ptr<class RigidbodyComponent> rigidbody;

	std::shared_ptr<class PlayerComponent> playerRef;
	bool dead{ false };

	void onBodyIntersect(class RigidbodyComponent& other);

	const float range{ 9.0f };
	const float speed{ 2.0f };
};

