#include "rigidbodyComponent.h"
#include "physics.h"
#include "ObjectChannels/collisionChannels.h"
#include <iostream>

RigidbodyComponent::RigidbodyComponent(CollisionComponent* collisionToAssociate, bool useCCD, bool activatePhysics) :
	PhysicEntity(collisionToAssociate->loadedPersistent),
	ccd(useCCD), physicsActivated(activatePhysics), useGravity(activatePhysics)
{
	associateCollision(collisionToAssociate);

	onCollisionRepulsed.registerObserver(this, Bind_1(&RigidbodyComponent::onCollision));
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
	if (associatedCollision)
	{
		associatedCollision->onCollisionIntersect.unregisterObserver(this);
	}

	associatedCollision = collisionToAssociate;
	if (associatedCollision)
	{
		//  do initialization things with the newly associated collision
		associatedCollision->onCollisionIntersect.registerObserver(this, Bind_1(&RigidbodyComponent::onCollisionIntersected));
	}
}


void RigidbodyComponent::updatePhysicsPreCollision(float dt)
{
	if (firstFrame) return;

	//  compute gravity in velocity
	if (useGravity)
	{
		if(gravityVelocity.y > Physics::Gravity * 2.0f)
			gravityVelocity.y += Physics::Gravity * dt * 2.5f;

		groundedLastFrame = onGround;
		onGround = false;
	}

	//  compute anticipated movement
	movement = (velocity + velocityOneFrame) * dt;
	gravityMovement = gravityVelocity * dt;
	velocityOneFrame = Vector3::zero;

	//  if rigidbody has no physic activated, it moves but without checking for collisions to repulse its movement
	if (!isPhysicsActivated())
	{
		associatedCollision->addPosition(movement);
		associatedCollision->addPosition(gravityMovement);
		movement = Vector3::zero;
		gravityMovement = Vector3::zero;
	}
}

void RigidbodyComponent::updatePhysicsPostCollision(float dt)
{
	if (firstFrame)
	{
		firstFrame = false;
		return;
	}

	if (!isPhysicsActivated()) return;


	//  inversed step mechanic - NEED REWORK WITH GRAVITY MOVEMENT
	if (getStepHeight() > 0.0f && groundedLastFrame && !isOnGround() && velocity.y < 0.0f)
	{
		Box box = associatedCollision->getEncapsulatingBox();
		RaycastHitInfos out;

		bool hit = Physics::AABBSweepRaycast(box.getCenterPoint(), box.getCenterPoint() + Vector3{0.0f, -stepHeight, 0.0f}, box, {"solid"}, out, 0.0f);
		if (hit)
		{
			if (out.hitNormal == Vector3::unitY)
			{
				movement += Vector3{ 0.0f, -out.hitDistance, 0.0f };
			}
		}
	}


	//  apply real movement (anticipated movement modified by the collisions during physics step)
	associatedCollision->addPosition(movement);
	associatedCollision->addPosition(gravityMovement);
	movement = Vector3::zero;
	gravityMovement = Vector3::zero;
}

void RigidbodyComponent::setPhysicsActivated(bool value)
{
	physicsActivated = value;
}

void RigidbodyComponent::setWeigth(float value)
{
	if (weight <= 0.0f) return;
	weight = value;
}

void RigidbodyComponent::setUseGravity(bool value)
{
	useGravity = value;
}

void RigidbodyComponent::setStepHeight(float value)
{
	stepHeight = value;
}

void RigidbodyComponent::applyComputedMovement(const Vector3& computedMovement)
{
	if (!isPhysicsActivated()) return;

	movement = computedMovement;
}

void RigidbodyComponent::applyComputedGravityMovement(const Vector3& computedGravityMovement)
{
	if (!isPhysicsActivated()) return;

	gravityMovement = computedGravityMovement;

	if (!(gravityMovement == computedGravityMovement)) gravityVelocity = Vector3::zero; //  TEMPORARY
}

void RigidbodyComponent::setVelocity(const Vector3& value)
{
	velocity = value;
}

void RigidbodyComponent::addVelocity(const Vector3& value)
{
	velocity += value;
}

Vector3 RigidbodyComponent::getVelocity() const 
{ 
	return velocity;
}

void RigidbodyComponent::addVelocityOneFrame(const Vector3& value)
{
	velocityOneFrame += value;
}

void RigidbodyComponent::setUseCCD(bool value)
{
	ccd = value;
}

void RigidbodyComponent::setTestChannels(std::vector<std::string> newTestChannels)
{
	testChannels = newTestChannels;
}

void RigidbodyComponent::addTestChannel(std::string newTestChannel)
{
	testChannels.push_back(newTestChannel);
}

std::vector<std::string> RigidbodyComponent::getTestChannels() const
{
	if (testChannels.empty()) return CollisionChannels::GetRegisteredTestChannel("TestEverything");

	return testChannels;
}

void RigidbodyComponent::resetIntersected()
{
	associatedCollision->resetIntersected();
}

void RigidbodyComponent::onCollisionIntersected(RigidbodyComponent& other)
{
	if (isPhysicsActivated() || !other.isPhysicsActivated()) return;

	other.addVelocityOneFrame(getVelocity());
}

void RigidbodyComponent::onCollision(const CollisionResponse& collisionResponse)
{
	if (collisionResponse.impactNormal == Vector3::negUnitY)
	{
		onGround = true;
		gravityVelocity = Vector3::zero;
	}
	//  might change that later to allow onGround even on non perfectly flat surfaces using dot product
	//  not necessary now since there is only AABB currently implemented in this engine
}
