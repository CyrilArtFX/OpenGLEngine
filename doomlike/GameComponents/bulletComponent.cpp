#include "bulletComponent.h"
#include <ECS/entity.h>
#include <Physics/ObjectChannels/collisionChannels.h>
#include <Assets/assetManager.h>

#include <Rendering/modelRendererComponent.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>


void BulletComponent::setupBullet(const Vector3& spawnPos, const Quaternion& spawnRot, const Vector3& bulletDirection, const float bulletVelocity, const float bulletLifetime)
{
	getOwner()->setPosition(spawnPos);
	getOwner()->setRotation(spawnRot);
	lifetime = bulletLifetime;

	bulletModel->setModel(&AssetManager::GetModel("bullet"));
	bulletModel->offset.setRotation(Quaternion{ Vector3::unitY, Maths::toRadians(90.0f) });
	bulletModel->offset.setScale(0.0002f);

	collision->setBox(Box{ Vector3::zero, Vector3{0.05f, 0.05f, 0.05f} });
	collision->setCollisionChannel("bullet");
	collision->setCollisionType(CollisionType::Solid);
	collision->useOwnerScaleForBoxSize = false;

	rigidbody->setTestChannels(CollisionChannels::GetRegisteredTestChannel("PlayerEntity"));
	rigidbody->setPhysicsActivated(true);
	rigidbody->setUseGravity(false);
	rigidbody->setVelocity(bulletDirection * bulletVelocity);

	rigidbody->onCollisionRepulsed.registerObserver(this, Bind_1(&BulletComponent::onBulletCollisionHit));
	collision->onCollisionIntersect.registerObserver(this, Bind_1(&BulletComponent::onBulletEntityHit));

	getOwner()->addGameplayTag("Bullet");

	setUpdateActivated(true);
}

void BulletComponent::deleteBullet()
{
	rigidbody->onCollisionRepulsed.unregisterObserver(this);
	collision->onCollisionIntersect.unregisterObserver(this);

	getOwner()->destroyEntity();
}

bool BulletComponent::isLifetimeOver() const
{
	return lifetime <= 0.0f;
}

void BulletComponent::onBulletCollisionHit(const CollisionResponse& hitResponse)
{
	rigidbody->onCollisionRepulsed.unregisterObserver(this);

	rigidbody->setVelocity(Vector3::zero);
	rigidbody->setUseGravity(true);
}

void BulletComponent::onBulletEntityHit(RigidbodyComponent& hitBody)
{
	if (hitBody.getOwner()->hasGameplayTag("Enemy"))
	{
		lifetime = 0.0f; //  allow the gun component to properly delete the bullet
	}
}

void BulletComponent::init()
{
	//  reset the value in case this component was used before (the component manager is a memory pool)
	lifetime = 0.0f;


	bulletModel = getOwner()->addComponentByClass<ModelRendererComponent>();
	collision = getOwner()->addComponentByClass<BoxAABBColComp>();
	rigidbody = getOwner()->addComponentByClass<RigidbodyComponent>();
	rigidbody->associateCollision(collision);

	setUpdateActivated(false); //  it will be activated one setupBullet has been called
}

void BulletComponent::exit()
{
	rigidbody->onCollisionRepulsed.unregisterObserver(this);
	collision->onCollisionIntersect.unregisterObserver(this);

	//  release shared pointers
	bulletModel = nullptr;
	collision = nullptr;
	rigidbody = nullptr;
}

void BulletComponent::update(float deltaTime)
{
	lifetime -= deltaTime;
}