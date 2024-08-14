#include "movingPlatform.h"
#include <ServiceLocator/locator.h>
#include <ServiceLocator/physics.h>

void MovingPlatform::load()
{
	Physics& physics = Locator::getPhysics();

	rigidbody = &physics.CreateRigidbodyComponent(new RigidbodyComponent(new BoxAABBColComp(Box::one, this, false, "solid"), false));

	setScale(Vector3{ 2.0f, 0.2f, 2.0f });
}

void MovingPlatform::setup(Vector3 pointA_, Vector3 pointB_, float timeAtoB_, float waitTime_)
{
	pointA = pointA_;
	pointB = pointB_;
	timeAtoB = timeAtoB_;
	waitTime = waitTime_;
	timer = 0.0f;
	waitTimer = 0.0f;
	reverse = false;

	setPosition(pointA);
	distance = Vector3::Distance(pointA, pointB);
	rigidbody->setVelocity((pointB - pointA) * (1.0f / timeAtoB));
}

void MovingPlatform::updateObject(float dt)
{
	if (paused || timeAtoB <= 0.0f || distance == 0.0f) return;

	if (waiting)
	{
		waitTimer -= dt;
		if (waitTimer <= 0.0f)
		{
			waitTimer = 0.0f;
			waiting = false;

			resume();
		}
		return;
	}

	if (reverse)
	{
		timer -= dt;
		if (timer <= 0.0f)
		{
			timer = 0.0f;
			reverse = false;
			rigidbody->setVelocity((pointB - pointA) * (1.0f / timeAtoB));
			if (waitTime > 0.0f)
			{
				waitTimer = waitTime;
				waiting = true;
				rigidbody->setVelocity(Vector3::zero);
			}
		}
	}
	else
	{
		timer += dt;
		if (timer >= timeAtoB)
		{
			timer = timeAtoB;
			reverse = true;
			rigidbody->setVelocity((pointA - pointB) * (1.0f / timeAtoB));
			if (waitTime > 0.0f)
			{
				waitTimer = waitTime;
				waiting = true;
				rigidbody->setVelocity(Vector3::zero);
			}
		}
	}
}

void MovingPlatform::pause()
{
	paused = true;
	rigidbody->setVelocity(Vector3::zero);
}

void MovingPlatform::resume()
{
	paused = false;
	if (waiting) return;
	rigidbody->setVelocity((reverse ? (pointA - pointB) : (pointB - pointA)) * (1.0f / timeAtoB));
}
