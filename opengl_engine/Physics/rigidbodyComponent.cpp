#include "rigidbodyComponent.h"
#include "physics.h"
#include <iostream>

RigidbodyComponent::RigidbodyComponent(CollisionComponent* collisionToAssociate, bool useCCD, bool activatePhysics) :
	PhysicEntity(collisionToAssociate->loadedPersistent),
	ccd(useCCD), physicsActivated(activatePhysics), useGravity(activatePhysics)
{
	associateCollision(collisionToAssociate);
}

RigidbodyComponent::~RigidbodyComponent()
{
	if (registered)
	{
		Physics::RemoveRigidbody(this);
	}

	onRigidbodyDelete.broadcast();

	delete associatedCollision;
}

void RigidbodyComponent::associateCollision(CollisionComponent* collisionToAssociate)
{
	associatedCollision = collisionToAssociate;
	if (associatedCollision)
	{
		//  do initialization things with the newly associated collision
	}
}


void RigidbodyComponent::updatePhysicsPreCollision(float dt)
{
	if (!isPhysicsActivated()) return;

	//  compute gravity in velocity
	if (useGravity)
	{
		if(velocity.y > Physics::Gravity)
			velocity.y += Physics::Gravity * dt * 15.0f;
	}

	//  compute anticipated movement
	movement = velocity * dt;
}

void RigidbodyComponent::updatePhysicsPostCollision(float dt)
{
	if (!isPhysicsActivated()) return;

	//  apply real movement (anticipated movement modified by the collisions during physics step)
	associatedCollision->addPosition(movement);
	movement = Vector3::zero;
}

void RigidbodyComponent::setPhysicsActivated(bool value)
{
	physicsActivated = value;
}

void RigidbodyComponent::setWeigth(float value)
{
	weight = value;
}

void RigidbodyComponent::setUseGravity(float value)
{
	useGravity = value;
}

void RigidbodyComponent::computeRepulsion(const Vector3& repulsion)
{
	//  compute real movement and velocity with repulsion
	movement += repulsion;
	

	//  absolutely not sure that it is a really good way to do this, it has no linear repulsion
	//  it will certainly be reworked later
	if (!Maths::samesign(velocity.x, repulsion.x) && repulsion.x != 0.0f)
	{
		velocity.x = 0.0f;
	}
	if (!Maths::samesign(velocity.y, repulsion.y) && repulsion.y != 0.0f)
	{
		velocity.y = 0.0f;
	}
	if (!Maths::samesign(velocity.z, repulsion.z) && repulsion.z != 0.0f)
	{
		velocity.z = 0.0f;
	}
}

void RigidbodyComponent::setVelocity(const Vector3& value)
{
	velocity = value;
}

Vector3 RigidbodyComponent::getVelocity() const 
{ 
	return velocity;
}

void RigidbodyComponent::setUseCCD(bool value)
{
	ccd = value;
}

void RigidbodyComponent::resetIntersected()
{
	associatedCollision->resetIntersected();
}
