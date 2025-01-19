#include "component.h"
#include "entity.h"

Component::Component(Entity* owner_) : owner(owner_)
{
	registerComponent();
	componentRegistered = true;
}

Component::~Component()
{
	if (componentRegistered)
	{
		unregisterComponent();
		componentRegistered = false;
	}
}

Entity* Component::getOwner() const
{
	return owner;
}