#include "triggerZone.h"

#include <Physics/physics.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>

void TriggerZone::setup(Vector3 position, Vector3 size)
{
	setPosition(position);
	rigidbody = &Physics::CreateRigidbodyComponent(new RigidbodyComponent(new BoxAABBColComp(Box{ Vector3::zero, size * 0.5f }, this, false, "trigger_zone", false, false), true));
	rigidbody->getAssociatedCollisionNonConst().onCollisionIntersect.registerObserver(this, Bind_1(&TriggerZone::onBodyIntersect));
	rigidbody->setTestChannels({ "player" });
	rigidbody->setUseGravity(false);
}

void TriggerZone::disableZone()
{
	rigidbody->setTestChannels({ "nothing lol" });
}

void TriggerZone::onBodyIntersect(RigidbodyComponent& other)
{
	if (other.getAssociatedCollision().getCollisionChannel() == "player")
	{
		onPlayerEnter.broadcast();
	}
}
