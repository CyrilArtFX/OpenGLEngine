#pragma once
#include <Objects/object.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Events/observer.h>

class BoxAABBColComp;

class Target : public Object, private Observer
{
public:
	void load() override;

	void onIntersectedByRaycast(RaycastType type, const Vector3& intersectionPoint);

private:
	BoxAABBColComp* collision{ nullptr };
};

