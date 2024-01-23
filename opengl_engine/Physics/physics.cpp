#include "physics.h"

#include <iostream>
#include <algorithm>


std::vector<CollisionComponent*> Physics::collisionsComponents;
std::vector<Raycast*> Physics::raycasts;


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

bool Physics::RaycastLine(const Vector3& start, const Vector3& end, RaycastHitInfos& outHitInfos)
{
	std::cout << "PHYSICS_INFO: Create a raycast line.\n";

	bool hit = false;

	raycasts.emplace_back(new Raycast(start, end));

	//  TEMP:
	raycasts.back()->setHitPos(Vector3{ 0.0f, 1.5f, 0.0f });

	const Ray& ray = raycasts.back()->getRay();

	for (auto& col : collisionsComponents)
	{
		hit = hit || col->resolveRaycast(ray, outHitInfos);
	}

	return hit;
}

void Physics::UpdatePhysics()
{
	//  reset the 'intersected last frame' parameter
	for (auto& col : collisionsComponents)
	{
		col->resetIntersected();
	}

	//  test the currently existing raycasts for debug drawing
	for (auto& col : collisionsComponents)
	{
		RaycastHitInfos out;
		for (auto& raycast : raycasts)
		{
			col->resolveRaycast(raycast->getRay(), out);
		}
	}
}

void Physics::ClearAllCollisions()
{
	std::cout << "PHYSICS_INFO: Clearing all collisions and raycasts.\n";

	for (auto& col : collisionsComponents)
	{
		col->registered = false;
	}

	collisionsComponents.clear();

	raycasts.clear();
}

void Physics::DrawCollisionsDebug(Material& debugMaterial)
{
	for (auto& col : collisionsComponents)
	{
		col->drawDebug(debugMaterial);
	}

	for (auto& raycast : raycasts)
	{
		raycast->drawDebugRaycast(debugMaterial);
	}
}
