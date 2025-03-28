#include "bullet.h"

#include <ServiceLocator/locator.h>
#include <Rendering/shader.h>

#include <Assets/assetManager.h>

#include <ServiceLocator/locator.h>
#include <ServiceLocator/physics.h>
#include <Physics/ObjectChannels/collisionChannels.h>


Bullet::Bullet(Vector3 spawnPos, Quaternion spawnRot, Vector3 direction_, float velocity_, float lifetime_) :
	rigidbody(&Locator::getPhysics().CreateRigidbodyComponent(new RigidbodyComponent(new BoxAABBColComp(Box{ Vector3::zero, Vector3{0.05f, 0.05f, 0.05f} }, &object, true, "bullet", CollisionType::Solid, false), true)))
{
	lifetime = lifetime_;

	Renderer& renderer = Locator::getRenderer();

	object.addModel(&AssetManager::GetModel("bullet"));

	object.setPosition(spawnPos);
	object.setRotation(spawnRot);
	object.incrementRotation(Quaternion{ object.getUp(), Maths::toRadians(90.0f)});
	object.setScale(0.0002f); //  faut pas mettre l'unit en kilometre sur maya hein (genre il abuse du bail le frero la)

	renderer.AddObject(&object);

	rigidbody->onCollisionRepulsed.registerObserver(this, Bind_1(&Bullet::onBulletWallHit));
	rigidbody->getAssociatedCollisionNonConst().onCollisionIntersect.registerObserver(this, Bind_1(&Bullet::onBulletEntityHit));
	rigidbody->onRigidbodyDelete.registerObserver(this, Bind_0(&Bullet::onRigidbodyDeleted));

	rigidbody->setTestChannels(CollisionChannels::GetRegisteredTestChannel("PlayerEntity"));

	rigidbody->setVelocity(direction_ * velocity_);
	rigidbody->setUseGravity(false);
}


void Bullet::destroy()
{
	if(rigidbody) delete rigidbody; //  this will properly remove the rigidbody from physics manager

	Renderer& renderer = Locator::getRenderer();

	renderer.RemoveObject(&object);
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
	if (hitBody.getAssociatedCollision().getCollisionChannel() == "enemy")
	{
		lifetime = 0.0f;
	}
}

void Bullet::onRigidbodyDeleted()
{
	rigidbody = nullptr;
}
