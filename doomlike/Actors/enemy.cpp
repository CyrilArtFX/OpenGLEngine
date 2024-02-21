#include "enemy.h"
#include <Physics/physics.h>
#include <Assets/assetManager.h>

void Enemy::load()
{
	addModel(&AssetManager::GetModel("enemy"));

	rigidbody = &Physics::CreateRigidbodyComponent(new RigidbodyComponent(new BoxAABBColComp(Box{Vector3::zero, Vector3{0.7f, 0.7f, 0.7f}}, this, false, "enemy"), false, true));

	rigidbody->setUseGravity(false);

	setScale(0.7f);
}