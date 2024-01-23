#pragma once
#include "collisionComponent.h"

#include <vector>

class Material;

class Physics
{
public:
	static CollisionComponent& CreateCollisionComponent(CollisionComponent* colComp);

	static void RemoveCollision(CollisionComponent* colComp);

	static void UpdatePhysics();

	/**
	* Remove every collisions that exists.
	* When collisions will be managed as proper components, this should better be changed.
	*/
	static void ClearAllCollisions();



	static void DrawCollisionsDebug(Material& debugMaterial);

private:
	static std::vector<CollisionComponent*> collisionsComponents;
};

