#include "transform.h"

Transform::Transform()
{
	computeMatrix();
}


void Transform::setPosition(Vector3 newPos)
{
	position = newPos;
	matrixDirty = true;
}

void Transform::setPosition(float newPosX, float newPosY, float newPosZ)
{
	setPosition(Vector3{ newPosX, newPosY, newPosZ });
}

void Transform::setScale(Vector3 newScale)
{
	scale = newScale;
	matrixDirty = true;
}

void Transform::setScale(float newScaleX, float newScaleY, float newScaleZ)
{
	setScale(Vector3{ newScaleX, newScaleY, newScaleZ });
}

void Transform::setScale(float newUniformScale)
{
	setScale(Vector3{ newUniformScale, newUniformScale, newUniformScale });
}

void Transform::setRotation(Quaternion newRotation)
{
	rotation = newRotation;
	matrixDirty = true;
}

void Transform::incrementRotation(Quaternion increment)
{
	rotation = Quaternion::concatenate(rotation, increment);
	matrixDirty = true;
}


void Transform::pasteTransform(Transform& transform)
{
	position = transform.getPosition();
	rotation = transform.getRotation();
	scale = transform.getScale();
	modelMatrix = transform.getModelMatrix();
	normalMatrix = transform.getNormalMatrix();
	matrixDirty = false;
}


const Matrix4 Transform::getModelMatrix()
{ 
	if (matrixDirty) computeMatrix();
	return modelMatrix;
}

const Matrix4 Transform::getNormalMatrix()
{
	if (matrixDirty) computeMatrix(); 
	return normalMatrix;
}

const Vector3 Transform::getForward() const
{
	return Vector3::transform(Vector3::unitX, rotation);
}

const Vector3 Transform::getUp() const
{
	return Vector3::transform(Vector3::unitY, rotation);
}

const Vector3 Transform::getRight() const 
{
	return Vector3::transform(Vector3::unitZ, rotation);
}


void Transform::computeMatrix()
{
	modelMatrix =
		Matrix4::createScale(scale) *
		Matrix4::createFromQuaternion(rotation) *
		Matrix4::createTranslation(position);

	normalMatrix = modelMatrix;
	normalMatrix.invert();
	normalMatrix.transpose();

	matrixDirty = false;
}
