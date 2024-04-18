#include "octTree.h"

OctTree::OctTree()
{
	region = Box::zero;
}

OctTree::OctTree(const Box& _region)
{
	region = _region;
}

OctTree::OctTree(const Box& _region, std::vector<CollisionComponent*> colObjs, std::vector<RigidbodyComponent*> rbodyObjs)
{
	region = _region;
	collisions = colObjs;
	rigidbodies = rbodyObjs;
}
