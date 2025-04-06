#pragma once
#include <ECS/component.h>
#include <Events/observer.h>
#include <Physics/raycast.h>

/**
* Components that print a message if its owner is hit by a line raycast.
* This component does not create the collision on its owner.
*/
class TargetComponent : public Component, public Observer
{
public:
	void onIntersectedByRaycast(RaycastType type, const Vector3& intersectionPoint);

private:
	void init() override;
	void exit() override;

	std::shared_ptr<class CollisionComponent> collision;
};

