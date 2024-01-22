#include "box.h"
#include <iostream>


//  default boxes values
const Box Box::zero(Vector3::zero, Vector3::zero);
const Box Box::one(Vector3::zero, Vector3::one);



Box::Box()
{
}

Box::Box(Vector3 centerPoint, Vector3 halfExtentsValues) : 
	center(centerPoint), halfExtents(halfExtentsValues)
{
	if (halfExtents < Vector3::zero)
	{
		std::cout << "BOX_ERROR: Tried to set negative half extents values.\n";
		halfExtents = Vector3::zero;
	}
}

void Box::setupWithMinAndMaxPoints(Vector3 minPoint, Vector3 maxPoint)
{
	if (!(minPoint <= maxPoint))
	{
		std::cout << "BOX_ERROR: Tried to setup with min and max points, but all min point values are not <= to max point values.\n";
		return;
	}

	halfExtents = maxPoint - minPoint;
	center = minPoint + halfExtents;
}

void Box::setCenterPoint(Vector3 centerPoint)
{
	center = centerPoint;
}

void Box::setHalfExtents(Vector3 halfExtentsValues)
{
	if (halfExtentsValues < Vector3::zero)
	{
		std::cout << "BOX_ERROR: Tried to set negative half extents values.\n";
	}

	halfExtents = halfExtentsValues;
}

Vector3 Box::getMinPoint()
{
	center - halfExtents;
}

Vector3 Box::getMaxPoint()
{
	center + halfExtents;
}