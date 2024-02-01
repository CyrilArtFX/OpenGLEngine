#include "bullet.h"

#include <Rendering/renderer.h>
#include <Rendering/shader.h>

#include <Assets/assetManager.h>

#include <Physics/physics.h>


Bullet::Bullet(Vector3 spawnPos, Quaternion spawnRot, Vector3 direction_, float velocity_, float lifetime_, Renderer* renderer_) :
	rigidbody(&Physics::CreateRigidbodyComponent(new RigidbodyComponent(new BoxAABBColComp(Box{ Vector3::zero, Vector3{0.05f, 0.05f, 0.05f} }, &object, false), true, false)))
{
	direction = direction_;
	velocity = velocity_;
	lifetime = lifetime_;
	renderer = renderer_;

	object.addModel(&AssetManager::GetModel("bullet"));

	object.setPosition(spawnPos);
	object.setRotation(spawnRot);
	object.setScale(0.1f, 0.1f, 0.2f);

	renderer->addObject(&object);

	rigidbody->onCollisionIntersect.registerObserver(this, Bind_0(&Bullet::onBulletHit));
	rigidbody->onRigidbodyDelete.registerObserver(this, Bind_0(&Bullet::onRigidbodyDeleted));

	rigidbody->updatePosLastFrame(); //  do this so that ccd is enabled the first frame, should be great to find a good way to do this
}


void Bullet::destroy()
{
	if(rigidbody) delete rigidbody; //  this will properly remove the rigidbody from physics manager

	renderer->removeObject(&object);
}


void Bullet::update(float dt)
{
	lifetime -= dt;

	object.setPosition(object.getPosition() + direction * velocity * dt);
}

void Bullet::onBulletHit()
{
	lifetime = 0.0f;
}

void Bullet::onRigidbodyDeleted()
{
	rigidbody = nullptr;
}
