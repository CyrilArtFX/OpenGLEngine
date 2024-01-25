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

bool Physics::RaycastLine(const Vector3& start, const Vector3& end, RaycastHitInfos& outHitInfos, float drawDebugTime)
{
	std::cout << "PHYSICS_INFO: Create a raycast line.\n";

	outHitInfos = RaycastHitInfos();

	bool hit = false;

	raycasts.emplace_back(new Raycast(start, end, drawDebugTime));

	const Ray& ray = raycasts.back()->getRay();

	for (auto& col : collisionsComponents)
	{
		bool col_hit = col->resolveRaycast(ray, outHitInfos);
		hit = hit || col_hit;
	}

	if (outHitInfos.hitCollision)
	{
		outHitInfos.hitCollision->forceIntersected();
		outHitInfos.hitCollision->onRaycastIntersect.broadcast();
	}


	if (hit) raycasts.back()->setHitPos(outHitInfos.hitLocation);

	return hit;
}

void Physics::UpdatePhysics(float dt)
{
	//  reset the 'intersected last frame' parameter
	for (auto& col : collisionsComponents)
	{
		col->resetIntersected();
	}

	//  delete raycasts that have run out of time
	for (int i = 0; i < raycasts.size(); i++)
	{
		raycasts[i]->updateDrawDebugTimer(dt);

		if (raycasts[i]->drawDebugTimerFinished())
		{
			delete raycasts[i];

			std::iter_swap(raycasts.begin() + i, raycasts.end() - 1);
			raycasts.pop_back();

			i--;
		}
	}

	//  test the currently existing raycasts for debug drawing
	for (auto& raycast : raycasts)
	{
		RaycastHitInfos out = RaycastHitInfos();
		for (auto& col : collisionsComponents)
		{
			col->resolveRaycast(raycast->getRay(), out);
		}
		if(out.hitCollision) out.hitCollision->forceIntersected();
	}
}

void Physics::ClearAllCollisions()
{
	std::cout << "PHYSICS_INFO: Clearing all collisions and raycasts.\n";

	for (auto col : collisionsComponents)
	{
		col->registered = false;
		delete col;
	}

	collisionsComponents.clear();

	for (auto raycast : raycasts)
	{
		delete raycast;
	}
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
