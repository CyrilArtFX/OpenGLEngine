#pragma once
#include "collisionComponent.h"
#include "rigidbodyComponent.h"
#include <Maths/Geometry/box.h>
#include "raycast.h"

#include <vector>

class Material;


class Physics
{
public:
	static CollisionComponent& CreateCollisionComponent(CollisionComponent* colComp);

	static void RemoveCollision(CollisionComponent* colComp);

	static RigidbodyComponent& CreateRigidbodyComponent(RigidbodyComponent* rigidbodyComp);

	static void RemoveRigidbody(RigidbodyComponent* rigidbodyComp);


	/**
	* Creates a Line Raycast from start to end.
	* Will return true if one (or more) collision intersect with the line.
	* In outHitInfos will be stored the informations of the nearest encountered collision.
	* For a raycast that don't draw debug, enter 0.0f to drawDebugTime.
	* For a raycast that never disappear from debug, enter negative value to drawDebugTime.
	*/
	static bool LineRaycast(const Vector3& start, const Vector3& end, RaycastHitInfos& outHitInfos = RaycastHitInfos::defaultInfos, float drawDebugTime = 5.0f, bool createOnScene = true);

	/**
	* Create an AABB Box Raycast at a location.
	* Will return true if one or more collision intersect with the box.
	* Currently no outHitInfos.
	* For a raycast that don't draw debug, enter 0.0f to drawDebugTime.
	* For a raycast that never disappear from debug, enter negative value to drawDebugTime.
	*/
	static bool AABBRaycast(const Vector3& location, const Box& aabbBox, float drawDebugTime = 5.0f, bool createOnScene = true);

	//  TODO: Make raycasts also test rigidbodies collisions
	//  Wait Object Channels before doing that otherwise it will make the step mechanic break (the aabb raycast will intersect the player)





	static void UpdatePhysics(float dt);

	/**
	* Remove every collisions and rigidbodies that exists.
	* When collisions will be managed as proper components, this should better be changed.
	*/
	static void ClearAllCollisions(bool engineClosing);



	static void DrawCollisionsDebug(Material& debugMaterial);



	static const float Gravity;

private:
	static std::vector<CollisionComponent*> collisionsComponents;
	static std::vector<RigidbodyComponent*> rigidbodiesComponents;
	static std::vector<Raycast*> raycasts; //  actually only used for storing raycast and drawing the feedback in the debug draw
};

