#pragma once
#include <Objects/object.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Events/observer.h>

class BoxAABBColComp;

class Target : public Object, private Observer
{
public:
	Target();

	void onIntersectedByRaycast(const Vector3& intersectionPoint);

private:
	BoxAABBColComp* collision;
};

