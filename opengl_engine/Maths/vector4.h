#pragma once
#include "maths.h"
#include <string>

/**
* Vector4 type is mainly useful for passing datas to shaders.
*/
struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

	explicit Vector4(float xP, float yP, float zP, float wP)
		: x(xP), y(yP), z(zP), w(wP) {}

	Vector4(const struct Vector3 vec3);

	void set(float xP, float yP, float zP, float wP);

	const float* getAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}


	/** operator -
	* Negate every components of the vector.
	*/
	Vector4 operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}

	/** operator ==
	* Returns true if x, y, z and w are equal to other's
	*/
	bool operator==(const Vector4& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	std::string toString() const
	{
		return std::to_string(x) + "  " + std::to_string(y) + "  " + std::to_string(z) + "  " + std::to_string(w);
	}

	static const Vector4 zero;
	static const Vector4 one;
};

