#include "target.h"
#include <ServiceLocator/locator.h>
#include <ServiceLocator/physics.h>
#include <iostream>

void Target::load()
{
	Physics& physics = Locator::getPhysics();

	collision = static_cast<BoxAABBColComp*>(&physics.CreateCollisionComponent(new BoxAABBColComp(Box::one, this, false, "solid")));
	
	collision->onRaycastIntersect.registerObserver(this, Bind_2(&Target::onIntersectedByRaycast));
}

void Target::onIntersectedByRaycast(RaycastType type, const Vector3& intersectionPoint)
{
	if (type != RaycastType::RaycastTypeLine) return;
	std::cout << "Target got hit by a raycast at coordinates " << intersectionPoint.toString() << std::endl;
}
