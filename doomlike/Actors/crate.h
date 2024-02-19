#pragma once
#include <Objects/object.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>

class Crate : public Object
{
public:
	void load() override;

private:
	RigidbodyComponent* rigidbody{ nullptr };
};