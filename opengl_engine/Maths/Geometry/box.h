#pragma once
#include <Maths/vector3.h>

/** Box
* Object that stores informations of a box
*/
class Box
{
public:
	Box();
	Box(const Vector3& centerPoint, const Vector3& halfExtentsValues);

	void setupWithMinAndMaxPoints(const Vector3& minPoint, const Vector3& maxPoint);
	void setCenterPoint(const Vector3& centerPoint);
	void setHalfExtents(const Vector3& halfExtentsValues);

	inline Vector3 getCenterPoint() const { return center; }
	inline Vector3 getHalfExtents() const { return halfExtents; }

	Vector3 getMinPoint() const;
	Vector3 getMaxPoint() const;

	Vector3 getPointOnPerimeter(const Vector3& point) const;
	Vector3 getNormalAtPoint(const Vector3& point) const;

	/**
	* This function is useful in case like Raycast AABB Sweep to find the hit normal of the nearest encountered collision.
	* Warning: this can produce really strange results if the two boxes are deeply colliding or if one box is contained inside the other one.
	*/
	Vector3 getNearestFaceNormal(const Box& other) const;

	void addHalfExtents(const Box& otherBox);

	std::string toString() const;


	static std::string ToString(const Box& box);
	static Box MinkowskiDifference(const Box& boxA, const Box& boxB);



private:
	Vector3 center{ Vector3::zero };
	Vector3 halfExtents{ Vector3::zero };



//  default boxes
public:
	static const Box zero;
	static const Box one;
};

