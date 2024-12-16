#pragma once
#include <ServiceLocator/physics.h>

/**
* The physics null service provider class.
*/
class NullPhysics : public Physics
{
public:
	CollisionComponent& CreateCollisionComponent(CollisionComponent* colComp) override { return *colComp; }
	void RemoveCollision(CollisionComponent* colComp) override {}

	RigidbodyComponent& CreateRigidbodyComponent(RigidbodyComponent* rigidbodyComp) override { return *rigidbodyComp; }
	void RemoveRigidbody(RigidbodyComponent* rigidbodyComp) override {}

	bool LineRaycast(const Vector3& start, const Vector3& end, const std::vector<std::string> testChannels = {}, RaycastHitInfos& outHitInfos = RaycastHitInfos::defaultInfos, float drawDebugTime = 5.0f, bool createOnScene = true) override { return false; }
	bool AABBRaycast(const Vector3& location, const Box& aabbBox, const std::vector<std::string> testChannels = {}, float drawDebugTime = 5.0f, bool createOnScene = true) override { return false; }
	bool AABBSweepRaycast(const Vector3& start, const Vector3& end, const Box& aabbBox, const std::vector<std::string> testChannels = {}, RaycastHitInfos& outHitInfos = RaycastHitInfos::defaultInfos, float drawDebugTime = 5.0f, bool createOnScene = true, bool forCollisionTest = false) override { return false; }

	void ClearAllCollisions(bool closeGame) override {}

	float GetGravityValue() override { return 0.0f; }

	void SetEnableInfoLogs(bool enable) override {}


private:
	void InitialisePhysics() override {}
	void UpdatePhysics(float dt) override {}
	void DrawCollisionsDebug(Material& debugMaterial) override {}
};