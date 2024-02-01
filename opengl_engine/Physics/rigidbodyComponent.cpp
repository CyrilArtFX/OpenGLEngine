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
	associatedCollision->addPosition(velocity * dt);
	if (useGravity) associatedCollision->addPosition(Physics::Gravity * dt);
}

void RigidbodyComponent::updatePhysicsPostCollision(float dt)
{
	if (!isPhysicsActivated()) return;
	associatedCollision->addPosition(currentResponse.repulsion);
	currentResponse.repulsion = Vector3::zero;
}

void RigidbodyComponent::updatePosLastFrame()
{
	if (!associatedCollision) return;
	associatedCollision->updatePosLastFrame();

	if (firstFrameCCD) firstFrameCCD = false;
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
