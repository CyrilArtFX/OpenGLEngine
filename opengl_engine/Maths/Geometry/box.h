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

	Vector3 getMinPoint();
	Vector3 getMaxPoint();

private:
	Vector3 center{ Vector3::zero };
	Vector3 halfExtents{ Vector3::zero };



//  default boxes
public:
	static const Box zero;
	static const Box one;
};

