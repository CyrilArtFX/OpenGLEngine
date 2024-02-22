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

Quaternion Quaternion::createLookAt(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	Vector3 z_axis = Vector3::normalize(target - pos);
	Vector3 x_axis = Vector3::normalize(Vector3::cross(up, z_axis));
	Vector3 y_axis = Vector3::normalize(Vector3::cross(z_axis, x_axis));

	float look_at_matrix[3][3] =
	{
		{ x_axis.x, y_axis.x, z_axis.x },
		{ x_axis.y, y_axis.y, z_axis.y },
		{ x_axis.z, y_axis.z, z_axis.z }
	};

	return fromRotationMatrix(look_at_matrix);
}

Quaternion Quaternion::fromRotationMatrix(const float mat[3][3])
{
	//  rotation matrix to quaternion code from https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
	Quaternion quat;

	float trace = mat[0][0] + mat[1][1] + mat[2][2];
	if (trace > 0.0f)
	{
		float s = 0.5f / sqrtf(trace + 1.0f);
		quat.w = 0.25f / s;
		quat.x = (mat[2][1] - mat[1][2]) * s;
		quat.y = (mat[0][2] - mat[2][0]) * s;
		quat.z = (mat[1][0] - mat[0][1]) * s;
	}
	else
	{
		if (mat[0][0] > mat[1][1] && mat[0][0] > mat[2][2])
		{
			float s = 2.0f * sqrtf(1.0f + mat[0][0] - mat[1][1] - mat[2][2]);
			quat.w = (mat[2][1] - mat[1][2]) / s;
			quat.x = 0.25f * s;
			quat.y = (mat[0][1] + mat[1][0]) / s;
			quat.z = (mat[0][2] + mat[2][0]) / s;
		}
		else if (mat[1][1] > mat[2][2])
		{
			float s = 2.0f * sqrtf(1.0f + mat[1][1] - mat[0][0] - mat[2][2]);
			quat.w = (mat[0][2] - mat[2][0]) / s;
			quat.x = (mat[0][1] + mat[1][0]) / s;
			quat.y = 0.25f * s;
			quat.z = (mat[1][2] + mat[2][1]) / s;
		}
		else
		{
			float s = 2.0f * sqrtf(1.0f + mat[2][2] - mat[0][0] - mat[1][1]);
			quat.w = (mat[1][0] - mat[0][1]) / s;
			quat.x = (mat[0][2] + mat[2][0]) / s;
			quat.y = (mat[1][2] + mat[2][1]) / s;
			quat.z = 0.25f * s;
		}
	}

	return quat;
}
