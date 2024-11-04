#include "vector4.h"
#include "vector3.h"

const Vector4 Vector4::zero(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::one(1.0f, 1.0f, 1.0f, 1.0f);

Vector4::Vector4(const Vector3 vec3)
{
	x = vec3.x;
	y = vec3.y;
	z = vec3.z;
	w = 1.0f;
}

void Vector4::set(float xP, float yP, float zP, float wP)
{
	x = xP;
	y = yP;
	z = zP;
	w = wP;
}
