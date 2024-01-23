#pragma once
#include <Maths/vector3.h>

/** Box
* Object that stores informations of a box
*/
class Box
{
public:
	Box();
	Box(Vector3 centerPoint, Vector3 halfExtentsValues);

	void setupWithMinAndMaxPoints(Vector3 minPoint, Vector3 maxPoint);
	void setCenterPoint(Vector3 centerPoint);
	void setHalfExtents(Vector3 halfExtentsValues);

	inline Vector3 getCenterPoint() const { return center; }
	inline Vector3 getHalfExtents() const { return halfExtents; }

	Vector3 getMinPoint() const;
	Vector3 getMaxPoint() const;

	std::string toString() const;


	static std::string ToString(const Box& box);

private:
	Vector3 center{ Vector3::zero };
	Vector3 halfExtents{ Vector3::zero };



//  default boxes
public:
	static const Box zero;
	static const Box one;
};

