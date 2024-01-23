#pragma once
#include <Maths/Geometry/ray.h>
#include <Rendering/Debug/line.h>
#include <Rendering/Debug/point.h>

struct RaycastHitInfos
{
	Vector3 hitLocation;
};

class Raycast
{
public:
	Raycast(const Vector3& startPoint, const Vector3& endPoint);
	Raycast() = delete;
	Raycast(const Raycast&) = delete;
	Raycast& operator=(const Raycast&) = delete;

	void drawDebugRaycast(Material& debugMaterial);

	void setHitPos(Vector3 hitPosition);

	inline const Ray& getRay() const { return ray; }

private:
	Ray ray;

	Line drawDebugLineOne;
	Line drawDebugLineTwo;
	Point drawDebugPointHit;

	bool hit{ false };
};

