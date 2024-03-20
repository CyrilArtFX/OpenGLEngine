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
		if(velocity.y > Physics::Gravity * 2.0f)
			velocity.y += Physics::Gravity * dt * 2.0f;

		groundedLastFrame = onGround;
		onGround = false;
	}

	//  compute anticipated movement
	movement = (velocity + velocityOneFrame) * dt;
	velocityOneFrame = Vector3::zero;

	//  if rigidbody has no physic activated, it moves but without checking for collisions to repulse its movement
	if (!isPhysicsActivated())
	{
		associatedCollision->addPosition(movement);
		movement = Vector3::zero;
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
	if (getStepHeight() > 0.0f && groundedLastFrame && !isOnGround())
	{
		Vector3 foot_pos = associatedCollision->getCenterDownPos();
		RaycastHitInfos out;


		//  this does not work for now. to make it work, it need a function that sweep a box through a line and return the first collision it encounters
		//  use it instead of this line raycast and it will be good

		bool hit = Physics::LineRaycast(foot_pos, foot_pos + Vector3{ 0.0f, -stepHeight, 0.0f }, { "solid" }, out, 0.0f);
		if (hit)
		{
			if (out.hitNormal == Vector3::negUnitY)
			{
				movement += Vector3{ 0.0f, -out.hitDistance, 0.0f };
			}
		}
	}





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
	if (weight <= 0.0f) return;
	weight = value;
}

void RigidbodyComponent::setUseGravity(float value)
{
	useGravity = value;
}

void RigidbodyComponent::setStepHeight(float value)
{
	stepHeight = value;
}

void RigidbodyComponent::computeRepulsion(const Vector3& repulsion)
{
	if (!isPhysicsActivated()) return;

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
	if (collisionResponse.impactNormal == Vector3::negUnitY) onGround = true;
	//  might change that later to allow onGround even on non perfectly flat surfaces using dot product
	//  not necessary now since there is only AABB currently implemented in this engine
}
