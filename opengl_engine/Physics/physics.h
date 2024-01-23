#pragma once
#include "collisionComponent.h"
#include "raycast.h"

#include <vector>

class Material;

class Physics
{
public:
	static CollisionComponent& CreateCollisionComponent(CollisionComponent* colComp);

	static void RemoveCollision(CollisionComponent* colComp);

	static bool RaycastLine(const Vector3& start, const Vector3& end, RaycastHitInfos& outHitInfos);

	static void UpdatePhysics();

	/**
	* Remove every collisions that exists.
	* When collisions will be managed as proper components, this should better be changed.
	*/
	static void ClearAllCollisions();



	static void DrawCollisionsDebug(Material& debugMaterial);

private:
	static std::vector<CollisionComponent*> collisionsComponents;
	static std::vector<Raycast*> raycasts; //  actually only used for storing raycast and drawing the feedback in the debug draw
};

