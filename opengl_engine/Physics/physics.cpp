#include "physics.h"

#include <iostream>
#include <algorithm>


std::vector<CollisionComponent*> Physics::collisionsComponents;


CollisionComponent& Physics::CreateCollisionComponent(CollisionComponent* colComp)
{
	std::cout << "PHYSICS_INFO: Create a collision.\n";
	collisionsComponents.push_back(colComp);

	CollisionComponent& col = *(collisionsComponents.back());
	col.registered = true;
	return col;
}

void Physics::RemoveCollision(CollisionComponent* colComp)
{
	auto iter = std::find(collisionsComponents.begin(), collisionsComponents.end(), colComp);
	if(iter == collisionsComponents.end())
	{
		std::cout << "PHYSICS_WARNING: Couldn't find a collision to remove.\n";
		return;
	}

	std::iter_swap(iter, collisionsComponents.end() - 1);
	CollisionComponent& col = *(collisionsComponents.back());
	col.registered = false;
	collisionsComponents.pop_back();

	std::cout << "PHYSICS_INFO: Successfully removed a collision.\n";
}

void Physics::ClearAllCollisions()
{
	std::cout << "PHYSICS_INFO: Clearing all collisions.\n";

	for (auto& col : collisionsComponents)
	{
		col->registered = false;
	}

	collisionsComponents.clear();
}
