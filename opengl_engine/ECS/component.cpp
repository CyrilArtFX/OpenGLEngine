#include "component.h"
#include "entity.h"

#include <iostream>

Component::Component()
{
	std::cout << "Component constructor called!\n";
}

Component::~Component()
{
	std::cout << "Component destructor called.\n";
}

Entity* Component::getOwner() const
{
	return owner;
}

void Component::setOwner(Entity* owner_)
{
	owner = owner_;
}
