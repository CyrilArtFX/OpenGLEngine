#include "component.h"
#include "entity.h"

Component::Component()
{
}

Component::~Component()
{
}

Entity* Component::getOwner() const
{
	return owner;
}

void Component::setOwner(Entity* owner_)
{
	owner = owner_;
}
