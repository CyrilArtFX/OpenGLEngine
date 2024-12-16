#include "ray.h"
#include <ServiceLocator/locator.h>


Ray::Ray()
{
}

Ray::Ray(const Vector3& origin, const Vector3& direction, float length) :
	rayOrigin(origin), rayDirection(direction), rayLength(length)
{
	if (rayDirection == Vector3::zero)
	{
		Locator::getLog().LogMessage_Category("Ray: Tried to set direction with a zero Vector3.", LogCategory::Warning);
		rayDirection = Vector3::unitX;
	}
	rayDirection.normalize();

	if (rayLength < 0.0f)
	{
		Locator::getLog().LogMessage_Category("Ray: Tried to set a negative length value.", LogCategory::Warning);
		rayLength = 0.0f;
	}
}


void Ray::setupWithStartEnd(const Vector3& startPos, const Vector3& endPos)
{
	if (startPos == endPos)
	{
		Locator::getLog().LogMessage_Category("Ray: Tried to set identical start and end positions.", LogCategory::Warning);
		rayOrigin = Vector3::zero;
		rayLength = 0.0f;
		rayDirection = Vector3::unitX;
		return;
	}


	rayOrigin = startPos;
	
	Vector3 start_to_end = endPos - startPos;
	rayLength = start_to_end.length();

	start_to_end.normalize();
	rayDirection = start_to_end;
}


void Ray::setOrigin(const Vector3& origin)
{
	rayOrigin = origin;
}

void Ray::setDirection(const Vector3& direction)
{
	rayDirection = direction;
	if (rayDirection == Vector3::zero)
	{
		Locator::getLog().LogMessage_Category("Ray: Tried to set direction with a zero Vector3.", LogCategory::Warning);
		rayDirection = Vector3::unitX;
	}
	rayDirection.normalize();
}

void Ray::setLength(float length)
{
	rayLength = length;
	if (rayLength < 0.0f)
	{
		Locator::getLog().LogMessage_Category("Ray: Tried to set a negative length value.", LogCategory::Warning);
		rayLength = 0.0f;
	}
}


Vector3 Ray::getStart() const
{
	return rayOrigin;
}

Vector3 Ray::getEnd() const
{
	return rayOrigin + rayDirection * rayLength;
}


std::string Ray::toString(bool displayStartAndEnd) const
{
	return Ray::ToString(*this, displayStartAndEnd);
}

std::string Ray::ToString(const Ray& ray, bool displayStartAndEnd)
{
	if (displayStartAndEnd) return "Start: " + ray.getStart().toString() + " | End: " + ray.getEnd().toString();
	else return "Origin: " + ray.rayOrigin.toString() + " | Direction: " + ray.rayDirection.toString() + " | Length: " + std::to_string(ray.rayLength);
}
