#include "movingPlatformComponent.h"
#include <ECS/entity.h>
#include <Physics/ObjectChannels/collisionChannels.h>
#include <Assets/assetManager.h>

#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>
#include <Audio/audioSourceComponent.h>


void MovingPlatformComponent::setupMovingPlatform(const Vector3& pointA_, const Vector3& pointB_, const float movementSpeed_, const float waitTime_, const bool debug_)
{
	pointA = pointA_;
	pointB = pointB_;
	timeAtoB = Vector3::Distance(pointA, pointB) / movementSpeed_;
	waitTime = waitTime_;
	timer = 0.0f;
	waitTimer = 0.0f;
	reverse = false;

	debug = debug_;

	getOwner()->setPosition(pointA);
	rigidbody->setVelocity((pointB - pointA) * (1.0f / timeAtoB));

	collision->setBox(Box::one);
	collision->setCollisionChannel("solid");

	rigidbody->setPhysicsActivated(false);
	rigidbody->setUseGravity(false);

	audioSource->setSpatialization(ChannelSpatialization::Channel3D);
	audioSource->playSound(AssetManager::GetSound("elevator"), -1);

	setUpdateActivated(true);

	if (debug)
	{
		Locator::getLog().LogMessageToScreen(
			"Moving Platform Setup: {Point A: " + pointA.toString() + "}  {Point B: " + pointB.toString() + "}  {Time A to B: " + std::to_string(timeAtoB) + "}  {Start Position: " + getOwner()->getPosition().toString() + "}", 
			Color::cyan, 99999999.0f, "moving_platform_debug_setup");
	}
}

void MovingPlatformComponent::pauseMovement()
{
	paused = true;
	rigidbody->setVelocity(Vector3::zero);
	audioSource->setPause(true);
}

void MovingPlatformComponent::resumeMovement()
{
	paused = false;
	if (waiting) return;

	rigidbody->setVelocity((reverse ? (pointA - pointB) : (pointB - pointA)) * (1.0f / timeAtoB));
	audioSource->setPause(false);
}

void MovingPlatformComponent::init()
{
	//  reset the values in case this component was used before (the component manager is a memory pool)
	pointA = Vector3::zero;
	pointB = Vector3::zero;
	timeAtoB = 0.0f;
	waitTime = 0.0f;
	timer = 0.0f;
	waitTimer = 0.0f;
	reverse = false;
	waiting = false;
	paused = false;


	collision = getOwner()->addComponentByClass<BoxAABBColComp>();
	rigidbody = getOwner()->addComponentByClass<RigidbodyComponent>();
	rigidbody->associateCollision(collision);
	audioSource = getOwner()->addComponentByClass<AudioSourceComponent>();

	setUpdateActivated(false); //  it will be activated once setupMovingPlatform has been called
}

void MovingPlatformComponent::exit()
{
	//  release shared pointers
	collision = nullptr;
	rigidbody = nullptr;
	audioSource = nullptr;
}

void MovingPlatformComponent::update(float deltaTime)
{
	if (debug)
	{
		updateDebug(deltaTime);
	}

	if (paused) return;

	if (waiting)
	{
		waitTimer -= deltaTime;
		if (waitTimer <= 0.0f)
		{
			waitTimer = 0.0f;
			waiting = false;

			resumeMovement();
		}
		return;
	}

	if (reverse)
	{
		timer -= deltaTime;
		if (timer <= 0.0f) //  reached point A
		{
			getOwner()->setPosition(pointA);
			timer = 0.0f;
			reverse = false;
			rigidbody->setVelocity((pointB - pointA) * (1.0f / timeAtoB));

			if (waitTime > 0.0f)
			{
				waitTimer = waitTime;
				waiting = true;
				rigidbody->setVelocity(Vector3::zero);

				audioSource->setPause(true);
			}
		}
	}
	else
	{
		timer += deltaTime;
		if (timer >= timeAtoB) //  reached point B
		{
			getOwner()->setPosition(pointB);
			timer = timeAtoB;
			reverse = true;
			rigidbody->setVelocity((pointA - pointB) * (1.0f / timeAtoB));
			if (waitTime > 0.0f)
			{
				waitTimer = waitTime;
				waiting = true;
				rigidbody->setVelocity(Vector3::zero);

				audioSource->setPause(true);
			}
		}
	}
}

void MovingPlatformComponent::updateDebug(float deltaTime)
{
	Locator::getLog().LogMessageToScreen("-- Moving Platform Debug New Frame --  {Delta Time: " + std::to_string(deltaTime) + "}", Color::white, 5.0f, "moving_platform_debug_deltatime");

	if (paused)
	{
		Locator::getLog().LogMessageToScreen("Moving Platform State: Paused", Color::magenta, 5.0f, "moving_platform_debug_state");
		Locator::getLog().LogMessageToScreen("Moving Platform Position: " + getOwner()->getPosition().toString(), Color::yellow, 5.0f, "moving_platform_debug_position");
		Locator::getLog().EraseLogIndexMessage("moving_platform_debug_timer");
		Locator::getLog().EraseLogIndexMessage("moving_platform_debug_velocity");
		return;
	}

	if (waiting)
	{
		Locator::getLog().LogMessageToScreen("Moving Platform State: Waiting", Color::magenta, 5.0f, "moving_platform_debug_state");
		Locator::getLog().LogMessageToScreen("Moving Platform Position: " + getOwner()->getPosition().toString(), Color::yellow, 5.0f, "moving_platform_debug_position");
		Locator::getLog().LogMessageToScreen("Moving Platform Wait Timer: " + std::to_string(waitTimer), Color::yellow, 5.0f, "moving_platform_debug_timer");
		Locator::getLog().EraseLogIndexMessage("moving_platform_debug_velocity");
		return;
	}

	if (reverse)
	{
		Locator::getLog().LogMessageToScreen("Moving Platform State: Moving reverse", Color::magenta, 5.0f, "moving_platform_debug_state");

	}
	else
	{
		Locator::getLog().LogMessageToScreen("Moving Platform State: Moving forward", Color::magenta, 5.0f, "moving_platform_debug_state");
	}

	Locator::getLog().LogMessageToScreen("Moving Platform Position: " + getOwner()->getPosition().toString(), Color::yellow, 5.0f, "moving_platform_debug_position");
	Locator::getLog().LogMessageToScreen("Moving Platform Timer: " + std::to_string(timer), Color::yellow, 5.0f, "moving_platform_debug_timer");
	Locator::getLog().LogMessageToScreen("Moving Platform Velocity: " + rigidbody->getVelocity().toString(), Color::yellow, 5.0f, "moving_platform_debug_velocity");
}