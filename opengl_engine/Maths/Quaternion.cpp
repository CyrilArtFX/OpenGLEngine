#include "quaternion.h"

const Quaternion Quaternion::identity(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion::Quaternion(float xP, float yP, float zP, float wP)
{
	set(xP, yP, zP, wP);
}

Quaternion::Quaternion(const Vector3& axis, float angle)
{
	float scalar = Maths::sin(angle / 2.0f);
	x = axis.x * scalar;
	y = axis.y * scalar;
	z = axis.z * scalar;
	w = Maths::cos(angle / 2.0f);
}

void Quaternion::set(float inX, float inY, float inZ, float inW)
{
	x = inX;
	y = inY;
	z = inZ;
	w = inW;
}

void Quaternion::conjugate()
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
}

void Quaternion::normalize()
{
	float len = length();
	x /= len;
	y /= len;
	z /= len;
	w /= len;
}

Quaternion Quaternion::fromEuler(const float yaw, const float roll, const float pitch)
{
	Quaternion quat;
	quat.x = Maths::cos(yaw / 2) * Maths::sin(roll / 2) * Maths::cos(pitch / 2) + Maths::sin(yaw / 2) * Maths::cos(roll / 2) * Maths::sin(pitch / 2);
	quat.y = Maths::sin(yaw / 2) * Maths::cos(roll / 2) * Maths::cos(pitch / 2) - Maths::cos(yaw / 2) * Maths::sin(roll / 2) * Maths::sin(pitch / 2);
	quat.z = Maths::cos(yaw / 2) * Maths::cos(roll / 2) * Maths::sin(pitch / 2) - Maths::sin(yaw / 2) * Maths::sin(roll / 2) * Maths::cos(pitch / 2);
	quat.w = Maths::cos(yaw / 2) * Maths::cos(roll / 2) * Maths::cos(pitch / 2) + Maths::sin(yaw / 2) * Maths::sin(roll / 2) * Maths::sin(pitch / 2);
	return quat;
}

Quaternion Quaternion::fromEuler(const Vector3& euler)
{
	return fromEuler(euler.x, euler.y, euler.z);
}

Vector3 Quaternion::toEuler(const Quaternion& quat)
{
	return Vector3::zero;
}
