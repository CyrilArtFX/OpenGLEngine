#include "triggerZone.h"

#include <ServiceLocator/locator.h>
#include <ServiceLocator/physics.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>

void TriggerZone::setup(Vector3 position, Vector3 size)
{
	Physics& physics = Locator::getPhysics();

	setPosition(position);
	triggerCol = &physics.CreateCollisionComponent(new BoxAABBColComp(Box{Vector3::zero, size * 0.5f}, this, false, "trigger_zone", CollisionType::Trigger, false, false));
	triggerCol->onTriggerEnter.registerObserver(this, Bind_1(&TriggerZone::onTriggerZoneEnter));
	disabled = false;
}

void TriggerZone::disableZone()
{
	disabled = true;
}

void TriggerZone::onTriggerZoneEnter(RigidbodyComponent& other)
{
	if (disabled) return;

	if (other.getAssociatedCollision().getCollisionChannel() == "player")
	{
		onPlayerEnter.broadcast();
	}
}
