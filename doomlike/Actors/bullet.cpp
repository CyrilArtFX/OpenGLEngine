#include "bullet.h"

#include <Rendering/renderer.h>
#include <Rendering/shader.h>

#include <Assets/assetManager.h>


Bullet::Bullet(Vector3 spawnPos, Quaternion spawnRot, Vector3 direction_, float velocity_, float lifetime_, Renderer* renderer_)
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
}


void Bullet::destroy()
{
	renderer->removeObject(&object);
}


void Bullet::update(float dt)
{
	lifetime -= dt;

	object.setPosition(object.getPosition() + direction * velocity * dt);
}
