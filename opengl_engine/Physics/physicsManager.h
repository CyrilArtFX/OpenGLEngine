#pragma once
#include <ServiceLocator/physics.h>
#include "collisionComponent.h"
#include "rigidbodyComponent.h"
#include <Maths/Geometry/box.h>
#include "raycast.h"

#include <vector>

class Material;

/**
* The physics service provider class.
*/
class PhysicsManager : public Physics
{
public:
	CollisionComponent& CreateCollisionComponent(CollisionComponent* colComp) override;
	void RemoveCollision(CollisionComponent* colComp) override;

	RigidbodyComponent& CreateRigidbodyComponent(RigidbodyComponent* rigidbodyComp) override;
	void RemoveRigidbody(RigidbodyComponent* rigidbodyComp) override;

	bool LineRaycast(const Vector3& start, const Vector3& end, const std::vector<std::string> testChannels = {}, RaycastHitInfos& outHitInfos = RaycastHitInfos::defaultInfos, float drawDebugTime = 5.0f, bool createOnScene = true) override;
	bool AABBRaycast(const Vector3& location, const Box& aabbBox, const std::vector<std::string> testChannels = {}, float drawDebugTime = 5.0f, bool createOnScene = true) override;
	bool AABBSweepRaycast(const Vector3& start, const Vector3& end, const Box& aabbBox, const std::vector<std::string> testChannels = {}, RaycastHitInfos& outHitInfos = RaycastHitInfos::defaultInfos, float drawDebugTime = 5.0f, bool createOnScene = true, bool forCollisionTest = false) override;

	void ClearAllCollisions(bool closeGame) override;

	float GetGravityValue() override;

	void SetEnableInfoLogs(bool enable) override;


private:
	void InitialisePhysics() override;
	void UpdatePhysics(float dt) override;
	void DrawCollisionsDebug(Material& debugMaterial) override;

	bool enableInfoLogs{ false };

	std::vector<CollisionComponent*> collisionsComponents;
	std::vector<RigidbodyComponent*> rigidbodiesComponents;
	std::vector<Raycast*> raycasts; //  actually only used for storing raycast and drawing the feedback in the debug draw
	const float gravity{ -9.8f };
};

