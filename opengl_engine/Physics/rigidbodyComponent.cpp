#include "rigidbodyComponent.h"
#include "physics.h"
#include "ObjectChannels/collisionChannels.h"
#include <iostream>

RigidbodyComponent::RigidbodyComponent(CollisionComponent* collisionToAssociate, bool activatePhysics) :
	PhysicEntity(collisionToAssociate->loadedPersistent), physicsActivated(activatePhysics), useGravity(activatePhysics)
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
		associatedCollision->setRigidbody(this);

		associatedCollision->onCollisionIntersect.registerObserver(this, Bind_1(&RigidbodyComponent::onCollisionIntersected));
	}
}


void RigidbodyComponent::updatePhysicsPreCollision(float dt)
{
	if (firstFrame) return;

	//  compute gravity in velocity
	if (useGravity)
	{
		if (gravityVelocity.y > Physics::Gravity * 2.0f)
			gravityVelocity.y += Physics::Gravity * dt * 2.5f;


		groundedLastFrame = onGround;
		onGround = false;
	}

	//  compute anticipated movement
	if (velocityOneFrame.y != 0.0f)
	{
		//  y velocity one frame will make the rigidbody start the test inside the collision that gave it
		associatedCollision->addPosition(Vector3{ 0.0f, velocityOneFrame.y, 0.0f } *dt);
		velocityOneFrame.y = 0.0f;
	}

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


	//  inversed step mechanic
	if (getStepHeight() > 0.0f && groundedLastFrame && !isOnGround() && gravityMovement.y < 0.0f)
	{
		Box box = associatedCollision->getEncapsulatingBox();
		RaycastHitInfos out;

		bool hit = Physics::AABBSweepRaycast(box.getCenterPoint() + gravityMovement, box.getCenterPoint() + Vector3{ 0.0f, -stepHeight, 0.0f }, box, { "solid" }, out, 0.0f);
		if (hit)
		{
			if (out.hitNormal == Vector3::unitY)
			{
				gravityMovement += Vector3{ 0.0f, -(out.hitDistance - Rigidbody::SECURITY_DIST), 0.0f };
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
}

bool RigidbodyComponent::checkStepMechanic(const CollisionComponent& collidedComp, const Vector3 aimedDestination, const Vector3 hitNormal, float& stepMovement) const
{
	if (stepHeight <= 0.0f)
		return false; //  continue only if this rigidbody use step mechanic

	if (!Maths::abs(Vector3::dot(Vector3::unitY, hitNormal)) < 0.5f)
		return false; //  continue only if collided with a wall

	Box body_box = associatedCollision->getEncapsulatingBox();
	body_box.setCenterPoint(aimedDestination);
	if (!collidedComp.resolveAABBRaycast(body_box, getTestChannels()))
		return false; //  continue only if body intersect with collided at aimed destination

	Box collided_box = collidedComp.getEncapsulatingBox();
	stepMovement = collided_box.getMaxPoint().y - body_box.getMinPoint().y + Rigidbody::SECURITY_DIST; //  compute needed step movement

	if (stepMovement > stepHeight)
		return false; //  continue only if needed step movement is lower than this rigidbody step height

	body_box.setCenterPoint(aimedDestination + Vector3{ 0.0f, stepMovement, 0.0f });
	if (Physics::AABBRaycast(Vector3::zero, body_box, getTestChannels(), 0.0f, true))
		return false; //  continue only if step destination is free

	return true;
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

void RigidbodyComponent::setGravityVelocity(const Vector3& value)
{
	gravityVelocity = value;
}

void RigidbodyComponent::addGravityVelocity(const Vector3& value)
{
	gravityVelocity += value;
}

Vector3 RigidbodyComponent::getGravityVelocity() const
{
	return gravityVelocity;
}

void RigidbodyComponent::addVelocityOneFrame(const Vector3& value)
{
	velocityOneFrame += value;
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
	if (collisionResponse.impactNormal == Vector3::unitY)
	{
		onGround = true;
		gravityVelocity = Vector3::zero;
	}
	//  might change that later to allow onGround even on non perfectly flat surfaces using dot product
	//  not necessary now since there is only AABB currently implemented in this engine
}
