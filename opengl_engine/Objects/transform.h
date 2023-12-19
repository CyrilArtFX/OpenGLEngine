#pragma once

#include <Maths/vector3.h>
#include <Maths/quaternion.h>
#include <Maths/matrix4.h>

class Transform
{
public:
	Transform();

	void setPosition(Vector3 newPos);
	void setPosition(float newPosX, float newPosY, float newPosZ);

	void setScale(Vector3 newScale);
	void setScale(float newScaleX, float newScaleY, float newScaleZ);
	void setScale(float newUniformScale);

	void setRotation(Quaternion newRotation);
	void incrementRotation(Quaternion increment);


	void pasteTransform(Transform& transform);


	const Vector3 getPosition() const { return position; }
	const Vector3 getScale() const { return scale; }
	const Quaternion getRotation() const { return rotation; }

	const Matrix4 getModelMatrix(); //  those functions can't be const because they need to call computeMatrix if matrix are dirty
	const Matrix4 getNormalMatrix();

	const Vector3 getForward() const;
	const Vector3 getUp() const;
	const Vector3 getRight() const;

private:
	void computeMatrix();

	Vector3 position{ Vector3::zero };
	Vector3 scale{ Vector3::one };
	Quaternion rotation{ Quaternion::identity };

	Matrix4 modelMatrix{ Matrix4::identity };
	Matrix4 normalMatrix{ Matrix4::identity };

	bool matrixDirty{ false };
};
