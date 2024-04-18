#pragma once
#include <Maths/Geometry/box.h>
#include <Physics/collisionComponent.h>
#include <Physics/rigidbodyComponent.h>

#include <vector>


class OctTree
{
public:
	OctTree();
	OctTree(const Box& _region);

private:
	OctTree(const Box& _region, std::vector<CollisionComponent*> colObjs, std::vector<RigidbodyComponent*> rbodyObjs);

	Box region;
	std::vector<CollisionComponent*> collisions;
	std::vector<RigidbodyComponent*> rigidbodies;

	OctTree* parent{ nullptr };

	OctTree* childNodes[8]{ nullptr };
	uint8_t activeNodes{ 0 };

	const float MIN_SIZE = 1.0f;
};

