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
	float yaw = 0.0f;
	float roll = 0.0f;
	float pitch = 0.0f;

	//  roll (x-axis rotation)
	double sinr_cosp = 2.0 * (quat.w * quat.x + quat.y * quat.z);
	double cosr_cosp = 1.0 - 2.0 * (quat.x * quat.x + quat.y * quat.y);
	roll = Maths::atan2(sinr_cosp, cosr_cosp);

	//  pitch (y-axis rotation)
	double sinp = 2.0 * (quat.w * quat.y - quat.z * quat.x);
	if (std::abs(sinp) >= 1) pitch = Maths::copysign(Maths::pi / 2.0f, sinp); //  use 90 degrees if out of range
	else pitch = std::asin(sinp);

	//  yaw (z-axis rotation)
	double siny_cosp = 2.0 * (quat.w * quat.z + quat.x * quat.y);
	double cosy_cosp = 1.0 - 2.0 * (quat.y * quat.y + quat.z * quat.z);
	yaw = Maths::atan2(siny_cosp, cosy_cosp);

	return Vector3{ yaw, roll, pitch };
}
