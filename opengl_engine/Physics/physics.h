#pragma once
#include "collisionComponent.h"

#include <vector>


class Physics
{
public:
	static CollisionComponent& CreateCollisionComponent(CollisionComponent* colComp);

	static void RemoveCollision(CollisionComponent* colComp);

	/**
	* Remove every collisions that exists.
	* When collisions will be managed as proper components, this should better be changed.
	*/
	static void ClearAllCollisions();

private:
	static std::vector<CollisionComponent*> collisionsComponents;
};

