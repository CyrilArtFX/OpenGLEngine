#include "rigidbodyComponent.h"
#include "physics.h"

RigidbodyComponent::RigidbodyComponent(CollisionComponent* collisionToAssociate, bool useCCD, bool activatePhysics) :
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

	//  compute anticipated movement
	movement = velocity * dt;
	if (useGravity) movement += Physics::Gravity * dt;
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

void RigidbodyComponent::setRealMovement(Vector3 realMovement)
{
	movement = realMovement;
}

void RigidbodyComponent::setVelocity(const Vector3& value)
{
	velocity = value;
}

Vector3 RigidbodyComponent::getVelocity() const 
{ 
	Vector3 ret_vel = velocity;
	if (useGravity) ret_vel += Physics::Gravity;
	return ret_vel;
}

void RigidbodyComponent::setUseCCD(bool value)
{
	ccd = value;
}

void RigidbodyComponent::resetIntersected()
{
	associatedCollision->resetIntersected();
}
