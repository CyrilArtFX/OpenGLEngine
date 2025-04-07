#pragma once
#include <ECS/component.h>
#include <Events/observer.h>
#include <Maths/Quaternion.h>


/**
* Add this component to an entity to make it a bullet.
* This component add every other needed components.
*/
class BulletComponent : public Component, public Observer
{
public:
	void setupBullet(const Vector3& spawnPos, const Quaternion& spawnRot, const Vector3& bulletDirection, const float bulletVelocity, const float bulletLifetime);
	void deleteBullet();

	bool isLifetimeOver() const;

	void onBulletCollisionHit(const struct CollisionResponse& hitResponse);
	void onBulletEntityHit(class RigidbodyComponent& hitBody);

protected:
	virtual void init() override;
	virtual void exit() override;
	virtual void update(float deltaTime) override;

	std::shared_ptr<class ModelRendererComponent> bulletModel;
	std::shared_ptr<class BoxAABBColComp> collision;
	std::shared_ptr<class RigidbodyComponent> rigidbody;

	float lifetime{ 0.0f };
};

