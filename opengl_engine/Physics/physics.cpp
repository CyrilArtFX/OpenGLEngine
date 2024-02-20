#include "physics.h"

#include "raycastLine.h"

#include "ObjectChannels/collisionChannels.h"

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

bool Physics::LineRaycast(const Vector3& start, const Vector3& end, const std::vector<std::string> testChannels, RaycastHitInfos& outHitInfos, float drawDebugTime, bool createOnScene)
{
	outHitInfos = RaycastHitInfos();

	bool hit = false;

	std::vector<std::string> test_channels = testChannels;
	if (test_channels.empty()) test_channels = CollisionChannels::GetRegisteredTestChannel("TestEverything");

	if (drawDebugTime != 0.0f)
	{
		std::cout << "PHYSICS_INFO: Create a raycast line.\n";

		raycasts.emplace_back(new RaycastLine(start, end, drawDebugTime, !createOnScene));

		RaycastLine& raycast = static_cast<RaycastLine&>(*raycasts.back());

		const Ray& ray = raycast.getRay();

		for (auto& col : collisionsComponents)
		{
			bool col_hit = col->resolveLineRaycast(ray, outHitInfos, test_channels);
			hit = hit || col_hit;
		}
		for (auto& body : rigidbodiesComponents)
		{
			const CollisionComponent& col = body->getAssociatedCollision();
			bool col_hit = col.resolveLineRaycast(ray, outHitInfos, test_channels);
			hit = hit || col_hit;
		}

		if (outHitInfos.hitCollision)
		{
			outHitInfos.hitCollision->onRaycastIntersect.broadcast(raycast.getRaycastType(), outHitInfos.hitLocation);
		}


		if (hit) raycast.setHitPos(outHitInfos.hitLocation);

		return hit;
	}
	else //  do not register the raycast in the list if it will not draw debug
	{
		RaycastLine* raycast = new RaycastLine(start, end, drawDebugTime);

		const Ray& ray = raycast->getRay();

		for (auto& col : collisionsComponents)
		{
			bool col_hit = col->resolveLineRaycast(ray, outHitInfos, test_channels);
			hit = hit || col_hit;
		}
		for (auto& body : rigidbodiesComponents)
		{
			const CollisionComponent& col = body->getAssociatedCollision();
			bool col_hit = col.resolveLineRaycast(ray, outHitInfos, test_channels);
			hit = hit || col_hit;
		}

		if (outHitInfos.hitCollision)
		{
			outHitInfos.hitCollision->onRaycastIntersect.broadcast(raycast->getRaycastType(), outHitInfos.hitLocation);
		}

		delete raycast;

		//  finally no need to set the hit pos on the raycast if it will not draw debug

		return hit;
	}
}

bool Physics::AABBRaycast(const Vector3& location, const Box& aabbBox, const std::vector<std::string> testChannels, float drawDebugTime, bool createOnScene)
{
	bool hit = false;

	std::vector<std::string> test_channels = testChannels;
	if (test_channels.empty()) test_channels = CollisionChannels::GetRegisteredTestChannel("TestEverything");

	std::vector<const CollisionComponent*> intersected_cols;

	if (drawDebugTime != 0.0f)
	{
		std::cout << "PHYSICS_INFO: Create a raycast AABB.\n";

		raycasts.emplace_back(new RaycastAABB(location, aabbBox, drawDebugTime));

		RaycastAABB& raycast = static_cast<RaycastAABB&>(*raycasts.back());

		const Box& box = raycast.getBox();

		for (auto col : collisionsComponents)
		{
			if (col->resolveAABBRaycast(box, test_channels))
			{
				hit = true;
				intersected_cols.push_back(col);
			}
		}
		for (auto body : rigidbodiesComponents)
		{
			const CollisionComponent& col = body->getAssociatedCollision();
			if (col.resolveAABBRaycast(box, testChannels))
			{
				hit = true;
				intersected_cols.push_back(&col);
			}
		}

		for (auto col : intersected_cols)
		{
			col->onRaycastIntersect.broadcast(raycast.getRaycastType(), location); //  location not really relevent here
		}

		if (hit) raycast.setHit();

		return hit;
	}
	else //  do not register the raycast in the list if it will not draw debug
	{
		RaycastAABB* raycast = new RaycastAABB(location, aabbBox, drawDebugTime, !createOnScene);

		const Box& box = raycast->getBox();

		for (auto col : collisionsComponents)
		{
			if (col->resolveAABBRaycast(box, test_channels))
			{
				hit = true;
				intersected_cols.push_back(col);
			}
		}
		for (auto body : rigidbodiesComponents)
		{
			const CollisionComponent& col = body->getAssociatedCollision();
			if (col.resolveAABBRaycast(box, testChannels))
			{
				hit = true;
				intersected_cols.push_back(&col);
			}
		}

		for (auto col : intersected_cols)
		{
			col->onRaycastIntersect.broadcast(raycast->getRaycastType(), location); //  location not really relevent here
		}

		delete raycast;

		//  finally no need to set the hit on the raycast if it will not draw debug

		return hit;
	}
}

void Physics::InitialisePhysics()
{
	CollisionChannels::RegisterTestChannel("TestEverything", { CollisionChannels::DefaultEverything() });
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
		rigidbody->updatePhysicsPreCollision(dt); //  also compute the anticipated movements for physics activated rigidbodies, and apply the movement for non-physics activated ones
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

	//  test all the rigidbodies
	for (int i = 0; i < rigidbodiesComponents.size(); i++)
	{
		RigidbodyComponent& rigidbody = *rigidbodiesComponents[i];
		if (!rigidbody.isAssociatedCollisionValid()) continue;
		bool rigidbody_physics = rigidbody.isPhysicsActivated();

		//  test rigidbody / collisions
		for (int j = 0; j < collisionsComponents.size(); j++)
		{
			CollisionComponent& col = *collisionsComponents[j];

			if (rigidbody_physics)
			{
				CollisionResponse response;

				bool hit = col.resolveRigidbody(rigidbody, response);

				if (hit)
				{
					rigidbody.getAssociatedCollision().forceIntersected();
					col.forceIntersected();
					rigidbody.onCollisionRepulsed.broadcast(response);
					col.onCollisionIntersect.broadcast(rigidbody);

					rigidbody.computeRepulsion(response.repulsion);
				}
			}
			else
			{
				bool hit = col.resolveCollision(rigidbody.getAssociatedCollision(), rigidbody.getTestChannels());

				if (hit)
				{
					rigidbody.getAssociatedCollision().forceIntersected();
					col.forceIntersected();

					col.onCollisionIntersect.broadcast(rigidbody);
				}
			}
		}

		//  test rigidbody / other rigidbodies
		for (int k = i + 1; k < rigidbodiesComponents.size(); k++)
		{
			RigidbodyComponent& other_rigidbody = *rigidbodiesComponents[k];
			if (!other_rigidbody.isAssociatedCollisionValid()) continue;
			bool other_rigidbody_physics = other_rigidbody.isPhysicsActivated();

			CollisionResponse response;
			CollisionResponse response_other;

			bool hit;
			if (rigidbody_physics && other_rigidbody_physics) hit = rigidbody.getAssociatedCollision().resolveRigidbodySelf(other_rigidbody, rigidbody);
			else if (!rigidbody_physics && other_rigidbody_physics) hit = rigidbody.getAssociatedCollision().resolveRigidbody(other_rigidbody, response_other);
			else if (rigidbody_physics) hit = other_rigidbody.getAssociatedCollision().resolveRigidbody(rigidbody, response);
			else hit = rigidbody.getAssociatedCollision().resolveCollision(other_rigidbody.getAssociatedCollision(), rigidbody.getTestChannels());

			if (hit)
			{
				rigidbody.getAssociatedCollision().forceIntersected();
				other_rigidbody.getAssociatedCollision().forceIntersected();

				if (rigidbody_physics && !other_rigidbody_physics)
				{
					rigidbody.onCollisionRepulsed.broadcast(response);
					rigidbody.computeRepulsion(response.repulsion);
				}
				else
				{
					rigidbody.getAssociatedCollisionNonConst().onCollisionIntersect.broadcast(other_rigidbody);
				}

				if (other_rigidbody_physics && !rigidbody_physics)
				{
					other_rigidbody.onCollisionRepulsed.broadcast(response_other);
					other_rigidbody.computeRepulsion(response_other.repulsion);
				}
				else
				{
					other_rigidbody.getAssociatedCollisionNonConst().onCollisionIntersect.broadcast(rigidbody);
				}
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
