#include "entity.h"
#include <algorithm>

Entity::Entity() : Transform()
{
}

Entity::~Entity()
{
	clearComponents();
}

void Entity::destroyEntity()
{
	//  at the end of the frame, the scene this entity is on will delete this entity
	entityDestoyed = true;
}

void Entity::removeComponent(Component* component)
{
	auto iter = std::find(components.begin(), components.end(), component);
	if (iter != components.end())
	{
		delete &iter;
		components.erase(iter);
	}
}

void Entity::clearComponents()
{
	for (auto& component : components)
	{
		delete component;
	}
	components.clear();
}