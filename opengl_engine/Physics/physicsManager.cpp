#include "physicsManager.h"

#include "raycastLine.h"
#include "AABB/raycastAABB.h"
#include "AABB/raycastAABBSweep.h"
#include "collisionTests.h"
#include "ObjectChannels/collisionChannels.h"
#include <ServiceLocator/locator.h>
#include <algorithm>



// ===============================================
//  ---- Collisions & Rigidbodies management ----
// ===============================================
void PhysicsManager::RegisterCollision(CollisionComponent* colComp)
{
	collisionsComponents.push_back(colComp);

	if(enableInfoLogs) Locator::getLog().LogMessage_Category("Physics: Registered a collision component.", LogCategory::Info);
}

void PhysicsManager::UnregisterCollision(CollisionComponent* colComp)
{
	auto iter = std::find(collisionsComponents.begin(), collisionsComponents.end(), colComp);
	if (iter == collisionsComponents.end())
	{
		Locator::getLog().LogMessage_Category("Physics: Failed to unregister a collision.", LogCategory::Error);
		return;
	}

	std::iter_swap(iter, collisionsComponents.end() - 1);
	collisionsComponents.pop_back();

	if (enableInfoLogs) Locator::getLog().LogMessage_Category("Physics: Successfully unregistered a collision.", LogCategory::Info);
}


RigidbodyComponent& PhysicsManager::CreateRigidbodyComponent(RigidbodyComponent* rigidbodyComp)
{
	if (enableInfoLogs) Locator::getLog().LogMessage_Category("Physics: Create a rigidbody.", LogCategory::Info);
	rigidbodiesComponents.push_back(rigidbodyComp);

	RigidbodyComponent& rigidbody = *(rigidbodiesComponents.back());
	rigidbody.registered = true;
	return rigidbody;
}

void PhysicsManager::RemoveRigidbody(RigidbodyComponent* rigidbodyComp)
{
	auto iter = std::find(rigidbodiesComponents.begin(), rigidbodiesComponents.end(), rigidbodyComp);
	if (iter == rigidbodiesComponents.end())
	{
		Locator::getLog().LogMessage_Category("Physics: Failed to remove a rigidbody", LogCategory::Error);
		return;
	}

	std::iter_swap(iter, rigidbodiesComponents.end() - 1);
	RigidbodyComponent& rigidbody = *(rigidbodiesComponents.back());
	rigidbody.registered = false;
	rigidbodiesComponents.pop_back();

	if (enableInfoLogs) Locator::getLog().LogMessage_Category("Physics: Successfully removed a rigidbody.", LogCategory::Info);
}



// ===============================================
//  ---------------- Raycasts -------------------
// ===============================================

bool PhysicsManager::LineRaycast(const Vector3& start, const Vector3& end, const std::vector<std::string> testChannels, RaycastHitInfos& outHitInfos, float drawDebugTime, bool createOnScene)
{
	outHitInfos = RaycastHitInfos();

	bool hit = false;

	std::vector<std::string> test_channels = testChannels;
	if (test_channels.empty()) test_channels = CollisionChannels::GetRegisteredTestChannel("TestEverything");

	if (drawDebugTime != 0.0f)
	{
		if (enableInfoLogs) Locator::getLog().LogMessage_Category("Physics: Create a raycast line.", LogCategory::Info);

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
		RaycastLine* raycast = new RaycastLine(start, end, drawDebugTime, !createOnScene);

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

bool PhysicsManager::AABBRaycast(const Vector3& location, const Box& aabbBox, const std::vector<std::string> testChannels, float drawDebugTime, bool createOnScene)
{
	bool hit = false;

	std::vector<std::string> test_channels = testChannels;
	if (test_channels.empty()) test_channels = CollisionChannels::GetRegisteredTestChannel("TestEverything");

	std::vector<const CollisionComponent*> intersected_cols;

	if (drawDebugTime != 0.0f)
	{
		if (enableInfoLogs) Locator::getLog().LogMessage_Category("Physics: Create a raycast AABB.", LogCategory::Info);

		raycasts.emplace_back(new RaycastAABB(location, aabbBox, drawDebugTime, !createOnScene));

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

bool PhysicsManager::AABBSweepRaycast(const Vector3& start, const Vector3& end, const Box& aabbBox, const std::vector<std::string> testChannels, RaycastHitInfos& outHitInfos, float drawDebugTime, bool createOnScene, bool forCollisionTest)
{
	outHitInfos = RaycastHitInfos();

	bool hit = false;

	std::vector<std::string> test_channels = testChannels;
	if (test_channels.empty()) test_channels = CollisionChannels::GetRegisteredTestChannel("TestEverything");

	if (drawDebugTime != 0.0f)
	{
		if (enableInfoLogs) Locator::getLog().LogMessage_Category("Physics: Create a raycast AABB sweep.", LogCategory::Info);

		raycasts.emplace_back(new RaycastAABBSweep(start, end, aabbBox, drawDebugTime, !createOnScene));

		RaycastAABBSweep& raycast = static_cast<RaycastAABBSweep&>(*raycasts.back());

		const Ray& ray = raycast.getRay();
		const Box& box = raycast.getBox();

		for (auto& col : collisionsComponents)
		{
			bool col_hit = col->resolveAABBSweepRaycast(ray, box, outHitInfos, test_channels, forCollisionTest);
			hit = hit || col_hit;
		}
		for (auto& body : rigidbodiesComponents)
		{
			const CollisionComponent& col = body->getAssociatedCollision();
			bool col_hit = col.resolveAABBSweepRaycast(ray, box, outHitInfos, test_channels, forCollisionTest);
			hit = hit || col_hit;
		}

		if (outHitInfos.hitCollision)
		{
			outHitInfos.hitCollision->onRaycastIntersect.broadcast(raycast.getRaycastType(), outHitInfos.hitLocation);
		}

		raycast.setValues(hit, outHitInfos.hitLocation);

		return hit;
	}
	else //  do not register the raycast in the list if it will not draw debug
	{
		RaycastAABBSweep* raycast = new RaycastAABBSweep(start, end, aabbBox, drawDebugTime, !createOnScene);

		const Ray& ray = raycast->getRay();
		const Box& box = raycast->getBox();

		for (auto& col : collisionsComponents)
		{
			bool col_hit = col->resolveAABBSweepRaycast(ray, box, outHitInfos, test_channels, forCollisionTest);
			hit = hit || col_hit;
		}
		for (auto& body : rigidbodiesComponents)
		{
			const CollisionComponent& col = body->getAssociatedCollision();
			bool col_hit = col.resolveAABBSweepRaycast(ray, box, outHitInfos, test_channels, forCollisionTest);
			hit = hit || col_hit;
		}

		if (outHitInfos.hitCollision)
		{
			outHitInfos.hitCollision->onRaycastIntersect.broadcast(raycast->getRaycastType(), outHitInfos.hitLocation);
		}

		delete raycast;

		//  finally no need to set the values of the raycast if it will not draw debug

		return hit;
	}
}



// ===============================================
//  ----------------- Update --------------------
// ===============================================

void PhysicsManager::InitialisePhysics()
{
	CollisionChannels::RegisterTestChannel("TestEverything", { CollisionChannels::DefaultEverything() });
}

void PhysicsManager::UpdatePhysics(float dt)
{
	//  reset the 'intersected last frame' parameter
	for (auto& col : collisionsComponents)
	{
		col->setDebugIntersected(false);
	}
	for (auto& rigidbody : rigidbodiesComponents)
	{
		rigidbody->resetIntersected();
		rigidbody->updatePhysicsPreCollision(dt); //  compute the anticipated movements for physics activated rigidbodies, and apply the movement for non-physics activated ones
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

		if (rigidbody.isPhysicsActivated())
		{
			//  compute body movement with collisions
			Vector3 body_movement = Vector3::zero;
			std::vector<CollisionHit> col_responses;
			std::vector<const CollisionComponent*> triggers_detected;
			bool hit = CollisionTests::RigidbodyCollideAndSlideAABB(rigidbody, false, body_movement, col_responses, triggers_detected);
			if (hit)
			{
				rigidbody.getAssociatedCollision().setDebugIntersected(true);
				for (int k = 0; k < col_responses.size(); k++)
				{
					CollisionResponse col_datas = { col_responses[k].impactPoint, col_responses[k].impactNormal };

					col_responses[k].collisionComponent.onCollisionIntersect.broadcast(rigidbody, col_datas);
					col_responses[k].collisionComponent.setDebugIntersected(true);

					if (col_responses[k].collisionComponent.ownedByRigidbody())
					{
						rigidbody.getAssociatedCollisionNonConst().onCollisionIntersect.broadcast(*(col_responses[k].collisionComponent.getOwningRigidbody()), col_datas);
					}

					if (k != 0) continue;
					rigidbody.onCollisionRepulsed.broadcast(CollisionResponse{ col_responses[k].impactPoint, col_responses[k].impactNormal });
				}
			}
			rigidbody.applyComputedMovement(body_movement);

			//  compute body gravity movement with collisions
			Vector3 gravity_movement = Vector3::zero;
			col_responses.clear();
			hit = CollisionTests::RigidbodyCollideAndSlideAABB(rigidbody, true, gravity_movement, col_responses, triggers_detected);
			if (hit)
			{
				rigidbody.getAssociatedCollision().setDebugIntersected(true);
				for (int k = 0; k < col_responses.size(); k++)
				{
					CollisionResponse col_datas = { col_responses[k].impactPoint, col_responses[k].impactNormal };

					col_responses[k].collisionComponent.onCollisionIntersect.broadcast(rigidbody, col_datas);
					col_responses[k].collisionComponent.setDebugIntersected(true);

					if (col_responses[k].collisionComponent.ownedByRigidbody())
					{
						rigidbody.getAssociatedCollisionNonConst().onCollisionIntersect.broadcast(*(col_responses[k].collisionComponent.getOwningRigidbody()), col_datas);
					}

					if (k != 0) continue;
					rigidbody.onCollisionRepulsed.broadcast(CollisionResponse{ col_responses[k].impactPoint, col_responses[k].impactNormal });
				}
			}
			rigidbody.applyComputedGravityMovement(gravity_movement);

			//  call event on detected triggers
			if (!triggers_detected.empty())
			{
				for (auto trigger_detected : triggers_detected)
				{
					trigger_detected->onTriggerEnter.broadcast(rigidbody);
					trigger_detected->setDebugIntersected(true);
				}
			}
		}
	}


	for (auto& rigidbody : rigidbodiesComponents)
	{
		rigidbody->updatePhysicsPostCollision(dt); // apply rigidbody movement for physic activated ones
	}
}


void PhysicsManager::DrawCollisionsDebug(Material& debugMaterial)
{
	for (auto& col : collisionsComponents)
	{
		col->drawDebug(debugMaterial);
	}

	for (auto& rigidbody : rigidbodiesComponents)
	{
		rigidbody->getAssociatedCollisionNonConst().drawDebug(debugMaterial);
	}

	for (auto& raycast : raycasts)
	{
		raycast->drawDebugRaycast(debugMaterial);
	}
}




float PhysicsManager::GetGravityValue()
{
	return gravity;
}

void PhysicsManager::SetEnableInfoLogs(bool enable)
{
	enableInfoLogs = enable;
}