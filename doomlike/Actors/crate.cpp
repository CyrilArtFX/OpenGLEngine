#include "crate.h"
#include <Physics/physics.h>

void Crate::load()
{
	rigidbody = &Physics::CreateRigidbodyComponent(new RigidbodyComponent(new BoxAABBColComp(Box::one, this, false), false, false));
}