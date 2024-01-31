#include "box.h"
#include <iostream>


//  default boxes values
const Box Box::zero(Vector3::zero, Vector3::zero);
const Box Box::one(Vector3::zero, Vector3{ 0.5f, 0.5f, 0.5f });



Box::Box()
{
}

Box::Box(const Vector3& centerPoint, const Vector3& halfExtentsValues) :
	center(centerPoint), halfExtents(halfExtentsValues)
{
	if (halfExtents < Vector3::zero)
	{
		std::cout << "BOX_ERROR: Tried to set negative half extents values.\n";
		halfExtents = Vector3::zero;
	}
}

void Box::setupWithMinAndMaxPoints(const Vector3& minPoint, const Vector3& maxPoint)
{
	if (!(minPoint <= maxPoint))
	{
		std::cout << "BOX_ERROR: Tried to setup with min and max points, but all min point values are not <= to max point values.\n";
		return;
	}

	halfExtents = maxPoint - minPoint;
	center = minPoint + halfExtents;
}

void Box::setCenterPoint(const Vector3& centerPoint)
{
	center = centerPoint;
}

void Box::setHalfExtents(const Vector3& halfExtentsValues)
{
	if (halfExtentsValues < Vector3::zero)
	{
		std::cout << "BOX_ERROR: Tried to set negative half extents values.\n";
	}

	halfExtents = halfExtentsValues;
}

Vector3 Box::getMinPoint() const
{
	return center - halfExtents;
}

Vector3 Box::getMaxPoint() const
{
	return center + halfExtents;
}

void Box::addHalfExtents(const Box& otherBox)
{
	halfExtents += otherBox.halfExtents;
}

std::string Box::toString() const
{
	return Box::ToString(*this);
}

std::string Box::ToString(const Box& box)
{
	return "Center: " + box.center.toString() + " | Half Extents: " + box.halfExtents.toString();
}
