#pragma once
#include <Maths/Geometry/ray.h>
#include <Rendering/Debug/line.h>
#include <Rendering/Debug/point.h>

#include <limits>

class CollisionComponent;

struct RaycastHitInfos
{
	RaycastHitInfos(Vector3 location, Vector3 normal, float distance, const CollisionComponent* collision) :
		hitLocation(location), hitNormal(normal), hitDistance(distance), hitCollision(collision) {}

	RaycastHitInfos() :
		hitLocation(Vector3::zero), hitNormal(Vector3::zero), hitDistance(std::numeric_limits<float>::max()), hitCollision(nullptr) {}

	Vector3 hitLocation{ Vector3::zero };
	Vector3 hitNormal{ Vector3::zero };
	float hitDistance{ std::numeric_limits<float>::max() }; //  used to get the nearest hit in case of multiple hits
	const CollisionComponent* hitCollision{ nullptr };

	static RaycastHitInfos defaultInfos;
};


class Raycast
{
public:
	Raycast(const Vector3& startPoint, const Vector3& endPoint, float drawDebugTime);
	Raycast() = delete;
	Raycast(const Raycast&) = delete;
	Raycast& operator=(const Raycast&) = delete;

	void drawDebugRaycast(Material& debugMaterial);

	void setHitPos(Vector3 hitPosition);

	void updateDrawDebugTimer(float dt);

	inline const Ray& getRay() const { return ray; }

	inline bool drawDebugTimerFinished() const { return drawDebugTimer == 0.0f; }

private:
	Ray ray;

	Line drawDebugLineOne;
	Line drawDebugLineTwo;
	Point drawDebugPointHit;

	bool hit{ false };

	float drawDebugTimer;
};

