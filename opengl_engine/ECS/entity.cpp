#include "entity.h"
#include "entityContainer.h"
#include <algorithm>

Entity::Entity(EntityContainer& containerRef_) : Transform(), containerRef(containerRef_)
{
}

Entity::~Entity()
{
	clearComponents();
}

void Entity::destroyEntity()
{
	//  at the end of the frame, the container this entity is on will delete this entity
	containerRef.addPendingEntity(this);
}

void Entity::removeComponent(Component* component)
{
	auto iter = std::find(components.begin(), components.end(), component);
	if (iter != components.end())
	{
		(*iter)->unregisterComponent();
		delete *iter;
		components.erase(iter);
	}
}

void Entity::clearComponents()
{
	for (auto& component : components)
	{
		component->unregisterComponent();
		delete component;
	}
	components.clear();
}