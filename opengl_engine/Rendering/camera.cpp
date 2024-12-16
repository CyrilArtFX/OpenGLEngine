#include "camera.h"

Camera::Camera() : Transform(), 
	yaw(YAW), pitch(PITCH), fov(FOV), camSpeed(SPEED), sensitivity(SENSITIVITY),
	pitchMin(PITCH_MIN), pitchMax(PITCH_MAX), fovMin(FOV_MIN), fovMax(FOV_MAX)
{
	setPosition(POSITION);
	computeYawPitch();
}


Matrix4 Camera::getViewMatrix()
{
	return Matrix4::createLookAt(getPosition(), getPosition() + getForward(), getUp());
}


void Camera::freecamKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = camSpeed * deltaTime;

	if (direction == Forward)
		setPosition(getPosition() + getForward() * velocity);

	if (direction == Backward)
		setPosition(getPosition() - getForward() * velocity);

	if (direction == Left)
		setPosition(getPosition() + getRight() * velocity);

	if (direction == Right)
		setPosition(getPosition() - getRight() * velocity);

	if (direction == Up)
		setPosition(getPosition() + Vector3::unitY * velocity);

	if (direction == Down)
		setPosition(getPosition() - Vector3::unitY * velocity);
}

void Camera::freecamMouseMovement(float xoffset, float yoffset)
{
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw -= xoffset;
	pitch = Maths::clamp(pitch + yoffset, pitchMin, pitchMax);
	computeYawPitch();
}

void Camera::freecamMouseScroll(float yoffset)
{
	fov = Maths::clamp(fov - yoffset, fovMin, fovMax);
}

Vector3 Camera::getFlatFront()
{
	Vector3 flat_front = getForward();
	flat_front.y = 0.0f;
	flat_front.normalize();
	return flat_front;
}

void Camera::setSpeed(float newSpeed)
{
	camSpeed = newSpeed;
}

void Camera::setSensitivity(float newSensitivity)
{
	sensitivity = newSensitivity;
}

void Camera::setPitchClamp(float min, float max)
{
	pitchMin = min;
	pitchMax = max;
}

void Camera::setFovClamp(float min, float max)
{
	fovMin = min;
	fovMax = max;
}

void Camera::computeYawPitch()
{
	setRotation(Quaternion::fromEuler(Maths::toRadians(yaw), 0.0f, Maths::toRadians(pitch)));
}


void Camera::copyCameraTransform(Camera& camera)
{
	fov = camera.fov;
	yaw = camera.yaw;
	pitch = camera.pitch;

	pasteTransform(camera);
}