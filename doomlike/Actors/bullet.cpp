#include "bullet.h"

#include <Rendering/renderer.h>
#include <Rendering/shader.h>

#include <Assets/assetManager.h>

#include <Physics/physics.h>

#include <iostream>


Bullet::Bullet(Vector3 spawnPos, Quaternion spawnRot, Vector3 direction_, float velocity_, float lifetime_, Renderer* renderer_) :
	rigidbody(&Physics::CreateRigidbodyComponent(new RigidbodyComponent(new BoxAABBColComp(Box{ Vector3::zero, Vector3{0.05f, 0.05f, 0.05f} }, &object, true, false), true, true)))
{
	lifetime = lifetime_;
	renderer = renderer_;

	object.addModel(&AssetManager::GetModel("bullet"));

	object.setPosition(spawnPos);
	object.setRotation(spawnRot);
	object.setScale(0.1f, 0.1f, 0.2f);

	renderer->addObject(&object);

	rigidbody->onCollisionRepulsed.registerObserver(this, Bind_1(&Bullet::onBulletWallHit));
	rigidbody->getAssociatedCollisionNonConst().onCollisionIntersect.registerObserver(this, Bind_1(&Bullet::onBulletEntityHit));
	rigidbody->onRigidbodyDelete.registerObserver(this, Bind_0(&Bullet::onRigidbodyDeleted));

	rigidbody->setVelocity(direction_ * velocity_);
	rigidbody->setUseGravity(false);
	rigidbody->setWeigth(0.00001f);
}


void Bullet::destroy()
{
	if(rigidbody) delete rigidbody; //  this will properly remove the rigidbody from physics manager

	renderer->removeObject(&object);
}


void Bullet::update(float dt)
{
	lifetime -= dt;
}

void Bullet::onBulletWallHit(const CollisionResponse& hitResponse)
{
	rigidbody->setVelocity(Vector3::zero);
	rigidbody->setUseGravity(true);
	rigidbody->onCollisionRepulsed.unregisterObserver(this);
}

void Bullet::onBulletEntityHit(RigidbodyComponent& hitBody)
{
	std::cout << "A bullet hit another rigidbody!\n";
}

void Bullet::onRigidbodyDeleted()
{
	rigidbody = nullptr;
}
