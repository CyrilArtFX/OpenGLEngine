#include "rigidbodyComponent.h"
#include "physics.h"

RigidbodyComponent::RigidbodyComponent(CollisionComponent* collisionToAssociate, bool useCCD) :
	ccd(useCCD)
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


void RigidbodyComponent::updatePosLastFrame()
{
	if (!associatedCollision) return;
	associatedCollision->updatePosLastFrame();

	if (firstFrameCCD) firstFrameCCD = false;
}

void RigidbodyComponent::setActivated(bool value)
{
	activated = value;
}

void RigidbodyComponent::setUseCCD(bool value)
{
	ccd = value;
}