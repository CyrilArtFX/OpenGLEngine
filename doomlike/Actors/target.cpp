#include "target.h"
#include <Physics/physics.h>
#include <iostream>

void Target::load()
{
	collision = static_cast<BoxAABBColComp*>(&Physics::CreateCollisionComponent(new BoxAABBColComp(Box::one, this, false)));
	
	collision->onRaycastIntersect.registerObserver(this, Bind_2(&Target::onIntersectedByRaycast));
}

void Target::onIntersectedByRaycast(RaycastType type, const Vector3& intersectionPoint)
{
	if (type != RaycastType::RaycastTypeLine) return;
	std::cout << "Target got hit by a redcast at coordinates " << intersectionPoint.toString() << std::endl;
}
