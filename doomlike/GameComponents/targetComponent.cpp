#include "targetComponent.h"
#include <ECS/entity.h>
#include <Physics/collisionComponent.h>
#include <ServiceLocator/locator.h>


void TargetComponent::onIntersectedByRaycast(RaycastType type, const Vector3& intersectionPoint)
{
	if (type != RaycastType::RaycastTypeLine) return;
	Locator::getLog().LogMessageToScreen("Doomlike: Target got hit by a line raycast at coordinates " + intersectionPoint.toString() + ".", Color::yellow, 5.0f);
}

void TargetComponent::init()
{
	collision = getOwner()->getComponentByClass<CollisionComponent>();

	if (!collision)
	{
		Locator::getLog().LogMessage_Category("Doomlike: A target component was added on an entity that doesn't have a collision component!", LogCategory::Warning);
		return;
	}

	collision->onRaycastIntersect.registerObserver(this, Bind_2(&TargetComponent::onIntersectedByRaycast));
}

void TargetComponent::exit()
{
	if (collision) collision->onRaycastIntersect.unregisterObserver(this);

	//  release shared ptr
	collision = nullptr;
}
