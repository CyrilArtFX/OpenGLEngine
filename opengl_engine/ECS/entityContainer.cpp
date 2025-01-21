#include "entityContainer.h"
#include "entity.h"

Entity* EntityContainer::createEntity()
{
	entities.push_back(new Entity());
	return entities.back();
}

void EntityContainer::updateEntities()
{
	//  delete destroyed entities
}

void EntityContainer::clearEntities()
{
	for (auto& entity : entities)
	{
		delete entity;
	}
	entities.clear();
}
