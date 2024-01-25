#include "bullet.h"

#include <Rendering/renderer.h>
#include <Rendering/shader.h>

#include <Assets/assetManager.h>

#include <Physics/physics.h>


Bullet::Bullet(Vector3 spawnPos, Quaternion spawnRot, Vector3 direction_, float velocity_, float lifetime_, Renderer* renderer_) :
	collision(&Physics::CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3::zero, Vector3{0.05f, 0.05f, 0.05f} }, &object, false)))
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

	collision->onCollisionDelete.registerObserver(this, std::bind(&Bullet::onCollisionDeleted, this));
}


void Bullet::destroy()
{
	if(collision) delete collision; //  this will properly remove the collision from physics manager

	renderer->removeObject(&object);
}


void Bullet::update(float dt)
{
	lifetime -= dt;

	object.setPosition(object.getPosition() + direction * velocity * dt);
}

void Bullet::onCollisionDeleted()
{
	collision = nullptr;
}
