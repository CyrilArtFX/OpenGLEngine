#pragma once
#include <Objects/object.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Events/ZeroParam/observer_zeroParam.h>

class BoxAABBColComp;

class Target : public Object, private Observer_ZeroParam
{
public:
	Target();

	void onEventObserved() override;

private:
	BoxAABBColComp* collision;
};

