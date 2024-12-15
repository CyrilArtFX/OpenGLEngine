#pragma once
#include <Maths/vector3.h>

/** Ray
* Object that stores informations of a ray
* Direction is already normalized.
*/
class Ray
{
public:
	Ray();
	Ray(const Vector3& origin, const Vector3& direction, float length);

	void setupWithStartEnd(const Vector3& startPos, const Vector3& endPos);
	void setOrigin(const Vector3& origin);
	void setDirection(const Vector3& direction);
	void setLength(float length);

	inline Vector3 getOrigin() const { return rayOrigin; }
	inline Vector3 getDirection() const { return rayDirection; }
	inline float getLength() const { return rayLength; }

	Vector3 getStart() const;
	Vector3 getEnd() const;

	std::string toString(bool displayStartAndEnd = false) const;


	static std::string ToString(const Ray& ray, bool displayStartAndEnd = false);


private:
	Vector3 rayOrigin{ Vector3::zero };
	Vector3 rayDirection{ Vector3::unitX };
	float rayLength{ 0.0f };
};