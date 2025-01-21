#pragma once
#include <vector>

class Entity;

class EntityContainer
{
public:
	virtual ~EntityContainer() {}

	Entity* createEntity();
	
private:
	std::vector<Entity*> entities;

	friend class Engine;
	void updateEntities();
	void clearEntities();
};

