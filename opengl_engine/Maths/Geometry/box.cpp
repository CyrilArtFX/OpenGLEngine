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

Vector3 Box::getNormalAtPoint(const Vector3& point) const
{
	//  this function can surely be greatly optimized by using maths
	//  I will need to check that later

	Vector3 min = getMinPoint();
	Vector3 max = getMaxPoint();
	Vector3 out_normal = Vector3::zero;

	if (point.x == min.x) out_normal.x = -1.0f;
	else if (point.x == max.x) out_normal.x = 1.0f;

	if (point.y == min.y) out_normal.y = -1.0f;
	else if (point.y == max.y) out_normal.y = 1.0f;

	if (point.z == min.z) out_normal.z = -1.0f;
	else if (point.z == max.z) out_normal.z = 1.0f;

	out_normal.normalize();
	return out_normal;
}

Vector3 Box::getNearestFaceNormal(const Box& other) const
{
	Vector3 out_normal = Vector3::zero;

	Vector3 min = getMinPoint();
	Vector3 max = getMaxPoint();
	Vector3 other_min = other.getMinPoint();
	Vector3 other_max = other.getMaxPoint();

	float nearest_face = 0.0f;

	//  X aligned faces
	float x_diff;
	if (center.x > other.center.x)
	{
		x_diff = Maths::abs(min.x - other_max.x);
		out_normal = Vector3::negUnitX;
	}
	else
	{
		x_diff = Maths::abs(other_min.x - max.x);
		out_normal = Vector3::unitX;
	}
	nearest_face = x_diff;

	//  Y aligned faces
	float y_diff;
	if (center.y > other.center.y)
	{
		y_diff = Maths::abs(min.y - other_max.y);
		if (y_diff == nearest_face)
		{
			out_normal += Vector3::negUnitY;
		}
		else if (y_diff < nearest_face)
		{
			out_normal = Vector3::negUnitY;
			nearest_face = y_diff;
		}
	}
	else
	{
		y_diff = Maths::abs(other_min.y - max.y);
		if (y_diff == nearest_face)
		{
			out_normal += Vector3::unitY;
		}
		else if (y_diff < nearest_face)
		{
			out_normal = Vector3::unitY;
			nearest_face = y_diff;
		}
	}

	//  Z aligned faces
	float z_diff;
	if (center.z > other.center.z)
	{
		z_diff = Maths::abs(min.z - other_max.z);
		if (z_diff == nearest_face)
		{
			out_normal += Vector3::negUnitZ;
		}
		else if (z_diff < nearest_face)
		{
			out_normal = Vector3::negUnitZ;
		}
	}
	else
	{
		z_diff = Maths::abs(other_min.z - max.z);
		if (z_diff == nearest_face)
		{
			out_normal += Vector3::unitZ;
		}
		else if (z_diff < nearest_face)
		{
			out_normal = Vector3::unitZ;
		}
	}

	out_normal.normalize();
	return out_normal;
}

void Box::addHalfExtents(const Box& otherBox)
{
	halfExtents += otherBox.halfExtents;
}

std::string Box::toString() const
{
	return Box::ToString(*this);
}

bool Box::containsPoint(const Vector3 point) const
{
	Vector3 min = getMinPoint();
	Vector3 max = getMaxPoint();

	return
		point.x >= min.x && point.x <= max.x &&
		point.y >= min.y && point.y <= max.y &&
		point.z >= min.z && point.z <= max.z;
}

std::string Box::ToString(const Box& box)
{
	return "Center: " + box.center.toString() + " | Half Extents: " + box.halfExtents.toString();
}

Box Box::MinkowskiDifference(const Box& boxA, const Box& boxB)
{
	Box md_box;

	Vector3 top_left = boxA.getMinPoint() - boxB.getMaxPoint();
	Vector3 extents = boxA.getHalfExtents() + boxB.getHalfExtents();

	md_box.setCenterPoint(top_left + extents);
	md_box.setHalfExtents(extents);

	return md_box;
}
