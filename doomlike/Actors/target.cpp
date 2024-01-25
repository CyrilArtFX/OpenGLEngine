#include "target.h"
#include <Physics/physics.h>
#include <iostream>

Target::Target() : 
	collision(static_cast<BoxAABBColComp*>(&Physics::CreateCollisionComponent(new BoxAABBColComp(Box::one, this))))
{
	collision->onRaycastIntersect.registerObserver(this);
}

void Target::onEventObserved()
{
	std::cout << "pitie faites que ca marche aaaaaaaaaa\n";
}
