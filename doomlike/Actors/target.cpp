#include "target.h"
#include <Physics/physics.h>
#include <iostream>

Target::Target() : 
	collision(static_cast<BoxAABBColComp*>(&Physics::CreateCollisionComponent(new BoxAABBColComp(Box::one, this))))
{
	collision->onRaycastIntersect.registerObserver(this, Bind_1(&Target::onIntersectedByRaycast));
}

void Target::onIntersectedByRaycast(const Vector3& intersectionPoint)
{
	std::cout << "Target got hit by a redcast at coordinates " << intersectionPoint.toString() << std::endl;
}