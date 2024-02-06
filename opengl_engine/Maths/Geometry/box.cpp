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

Vector3 Box::getPointOnPerimeter(const Vector3& point) const
{
	Vector3 point_perimeter;
	Vector3 min = getMinPoint();
	Vector3 max = getMaxPoint();

	point_perimeter.x = Maths::clamp(point.x, min.x, max.x);
	point_perimeter.y = Maths::clamp(point.y, min.y, max.y);
	point_perimeter.z = Maths::clamp(point.z, min.z, max.z);

	float dist_min_x = Maths::abs(point_perimeter.x - min.x);
	float dist_max_x = Maths::abs(point_perimeter.x - max.x);
	float dist_min_y = Maths::abs(point_perimeter.y - min.y);
	float dist_max_y = Maths::abs(point_perimeter.y - max.y);
	float dist_min_z = Maths::abs(point_perimeter.z - min.z);
	float dist_max_z = Maths::abs(point_perimeter.z - max.z);

	float min_dist = Maths::min(dist_min_x, Maths::min(dist_max_x, Maths::min(dist_min_y, Maths::min(dist_max_y, Maths::min(dist_min_z, dist_max_z)))));
	
	if (min_dist == dist_min_x)
	{
		point_perimeter.x = min.x;
		return point_perimeter;
	}
	if (min_dist == dist_max_x)
	{
		point_perimeter.x = max.x;
		return point_perimeter;
	}
	if (min_dist == dist_min_y)
	{
		point_perimeter.y = min.y;
		return point_perimeter;
	}
	if (min_dist == dist_max_y)
	{
		point_perimeter.y = max.y;
		return point_perimeter;
	}
	if (min_dist == dist_min_z)
	{
		point_perimeter.z = min.z;
		return point_perimeter;
	}

	//  min_dist == dist_max_z
	point_perimeter.z = max.z;
	return point_perimeter;
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
