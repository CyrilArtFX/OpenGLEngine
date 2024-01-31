#pragma once
#include "collisionComponent.h"
#include "raycast.h"

#include <vector>

class Material;

class Physics
{
public:
	static CollisionComponent& CreateCollisionComponent(CollisionComponent* colComp, bool useCCD = false);

	static void RemoveCollision(CollisionComponent* colComp);

	/**
	* Creates a Line Raycast from start to end.
	* In outHitInfos will be stored the informations of the nearest encountered collision.
	* For a raycast that don't draw debug, enter 0.0f to drawDebugTime.
	* For a raycast that never disappear from debug, enter negative value to drawDebugTime.
	*/
	static bool RaycastLine(const Vector3& start, const Vector3& end, RaycastHitInfos& outHitInfos = RaycastHitInfos::defaultInfos, float drawDebugTime = 5.0f);

	static void UpdatePhysics(float dt);

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

