#include "movingPlatform.h"
#include <Physics/physics.h>

void MovingPlatform::load()
{
	rigidbody = &Physics::CreateRigidbodyComponent(new RigidbodyComponent(new BoxAABBColComp(Box::one, this, false, "solid"), false, false));

	setScale(Vector3{ 2.0f, 0.2f, 2.0f });
}

void MovingPlatform::setup(Vector3 pointA_, Vector3 pointB_, float timeAtoB_)
{
	pointA = pointA_;
	pointB = pointB_;
	timeAtoB = timeAtoB_;
	timer = 0.0f;
	reverse = false;

	setPosition(pointA);
	distance = Vector3::Distance(pointA, pointB);
	rigidbody->setVelocity((pointB - pointA) * (1.0f / timeAtoB));
}

void MovingPlatform::updateObject(float dt)
{
	if (timeAtoB <= 0.0f || distance == 0.0f) return;

	if (reverse)
	{
		timer -= dt;
		if (timer <= 0.0f)
		{
			timer = 0.0f;
			reverse = false;
			rigidbody->setVelocity((pointB - pointA) * (1.0f / timeAtoB));
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
		}
	}
}
