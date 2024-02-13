#include "physics.h"

#include <iostream>
#include <algorithm>


std::vector<CollisionComponent*> Physics::collisionsComponents;
std::vector<RigidbodyComponent*> Physics::rigidbodiesComponents;
std::vector<Raycast*> Physics::raycasts;

const float Physics::Gravity = -9.8f;


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
	if (iter == collisionsComponents.end())
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

RigidbodyComponent& Physics::CreateRigidbodyComponent(RigidbodyComponent* rigidbodyComp)
{
	std::cout << "PHYSICS_INFO: Create a rigidbody.\n";
	rigidbodiesComponents.push_back(rigidbodyComp);

	RigidbodyComponent& rigidbody = *(rigidbodiesComponents.back());
	rigidbody.registered = true;
	return rigidbody;
}

void Physics::RemoveRigidbody(RigidbodyComponent* rigidbodyComp)
{
	auto iter = std::find(rigidbodiesComponents.begin(), rigidbodiesComponents.end(), rigidbodyComp);
	if (iter == rigidbodiesComponents.end())
	{
		std::cout << "PHYSICS_WARNING: Couldn't find a rigidbody to remove.\n";
		return;
	}

	std::iter_swap(iter, rigidbodiesComponents.end() - 1);
	RigidbodyComponent& rigidbody = *(rigidbodiesComponents.back());
	rigidbody.registered = false;
	rigidbodiesComponents.pop_back();

	std::cout << "PHYSICS_INFO: Successfully removed a rigidbody.\n";
}

bool Physics::RaycastLine(const Vector3& start, const Vector3& end, RaycastHitInfos& outHitInfos, float drawDebugTime, bool createOnScene)
{
	outHitInfos = RaycastHitInfos();

	bool hit = false;

	if (drawDebugTime != 0.0f)
	{
		std::cout << "PHYSICS_INFO: Create a raycast line.\n";

		raycasts.emplace_back(new Raycast(start, end, drawDebugTime, !createOnScene));

		const Ray& ray = raycasts.back()->getRay();

		for (auto& col : collisionsComponents)
		{
			bool col_hit = col->resolveRaycast(ray, outHitInfos);
			hit = hit || col_hit;
		}

		if (outHitInfos.hitCollision)
		{
			outHitInfos.hitCollision->forceIntersected();
			outHitInfos.hitCollision->onRaycastIntersect.broadcast(outHitInfos.hitLocation);
		}


		if (hit) raycasts.back()->setHitPos(outHitInfos.hitLocation);

		return hit;
	}
	else //  do not register the raycast in the list if it will not draw debug
	{
		Raycast* raycast = new Raycast(start, end, drawDebugTime);

		const Ray& ray = raycast->getRay();

		for (auto& col : collisionsComponents)
		{
			bool col_hit = col->resolveRaycast(ray, outHitInfos);
			hit = hit || col_hit;
		}

		if (outHitInfos.hitCollision)
		{
			//  also do not set the collision intersected if it will not draw debug
			outHitInfos.hitCollision->onRaycastIntersect.broadcast(outHitInfos.hitLocation);
		}

		delete raycast;

		//  finally no need to set the hit pos on the raycast if it will not draw debug

		return hit;
	}
}

void Physics::UpdatePhysics(float dt)
{
	//  reset the 'intersected last frame' parameter
	for (auto& col : collisionsComponents)
	{
		col->resetIntersected();
	}
	for (auto& rigidbody : rigidbodiesComponents)
	{
		rigidbody->resetIntersected();
		rigidbody->updatePhysicsPreCollision(dt); //  also compute the anticipated movements for physics activated rigidbodies
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
		if (out.hitCollision) out.hitCollision->forceIntersected();
	}

	//  test all the rigidbodies
	for (int i = 0; i < rigidbodiesComponents.size(); i++)
	{
		RigidbodyComponent& rigidbody = *rigidbodiesComponents[i];
		if (!rigidbody.isAssociatedCollisionValid()) continue;

		//  test rigidbody / collisions
		for (int j = 0; j < collisionsComponents.size(); j++)
		{
			CollisionComponent& col = *collisionsComponents[j];

			CollisionResponse response;

			bool hit = col.resolveRigidbody(rigidbody, response);

			if (hit)
			{
				rigidbody.getAssociatedCollision().forceIntersected();
				col.forceIntersected();
				rigidbody.onCollisionIntersect.broadcast(response);

				rigidbody.computeRepulsion(response.repulsion);
			}
		}

		//  test rigidbody / other rigidbodies
		for (int k = i + 1; k < rigidbodiesComponents.size(); k++)
		{
			RigidbodyComponent& other_rigidbody = *rigidbodiesComponents[k];
			if (!other_rigidbody.isAssociatedCollisionValid()) continue;

			CollisionResponse response;
			CollisionResponse response_other;

			bool hit = rigidbody.getAssociatedCollision().resolveRigidbodySelf(other_rigidbody, response, rigidbody, response_other);

			if (hit)
			{
				rigidbody.getAssociatedCollision().forceIntersected();
				other_rigidbody.getAssociatedCollision().forceIntersected();
				rigidbody.onCollisionIntersect.broadcast(response);
				other_rigidbody.onCollisionIntersect.broadcast(response_other);

				rigidbody.computeRepulsion(response.repulsion);
				other_rigidbody.computeRepulsion(response_other.repulsion);
			}
		}

		rigidbody.updatePhysicsPostCollision(dt); //  apply rigidbody real movement
	}
}

void Physics::ClearAllCollisions(bool engineClosing)
{
	if (engineClosing) 
	{
		std::cout << "PHYSICS_INFO: Clearing all collisions, rigidbodies and raycasts.\n";

		for (auto col : collisionsComponents)
		{
			col->registered = false;
			delete col;
		}
		collisionsComponents.clear();

		for (auto rigidbody : rigidbodiesComponents)
		{
			rigidbody->registered = false;
			delete rigidbody;
		}
		rigidbodiesComponents.clear();

		for (auto raycast : raycasts)
		{
			delete raycast;
		}
		raycasts.clear();

		return;
	}
	
	std::cout << "PHYSICS_INFO: Clearing active scene collisions, rigidbodies and raycasts.\n";

	std::vector<CollisionComponent*> game_collisions;
	for (auto col : collisionsComponents)
	{
		if (col->loadedPersistent)
		{
			game_collisions.push_back(col);
			continue;
		}

		col->registered = false;
		delete col;
	}
	collisionsComponents.clear();
	collisionsComponents = game_collisions;

	std::vector<RigidbodyComponent*> game_rigidbodies;
	for (auto rigidbody : rigidbodiesComponents)
	{
		if (rigidbody->loadedPersistent)
		{
			game_rigidbodies.push_back(rigidbody);
			continue;
		}

		rigidbody->registered = false;
		delete rigidbody;
	}
	rigidbodiesComponents.clear();
	rigidbodiesComponents = game_rigidbodies;

	std::vector<Raycast*> game_raycasts;
	for (auto raycast : raycasts)
	{
		if (raycast->loadedPersistent)
		{
			game_raycasts.push_back(raycast);
			continue;
		}

		delete raycast;
	}
	raycasts.clear();
	raycasts = game_raycasts;
}

void Physics::DrawCollisionsDebug(Material& debugMaterial)
{
	for (auto& col : collisionsComponents)
	{
		col->drawDebug(debugMaterial);
	}

	for (auto& rigidbody : rigidbodiesComponents)
	{
		rigidbody->getAssociatedCollision().drawDebug(debugMaterial);
	}

	for (auto& raycast : raycasts)
	{
		raycast->drawDebugRaycast(debugMaterial);
	}
}
