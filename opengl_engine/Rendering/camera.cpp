#include "camera.h"
#include <iostream>

Camera::Camera(Vector3 position_, float yaw_, float pitch_, float fov_) :
	Transform(), yaw(yaw_), pitch(pitch_), fov(fov_), camSpeed(SPEED), sensitivity(SENSITIVITY),
	pitchMin(PITCH_MIN), pitchMax(PITCH_MAX), fovMin(FOV_MIN), fovMax(FOV_MAX)
{
	setPosition(position_);
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
	/*xoffset *= sensitivity;
	yoffset *= sensitivity;
	std::cout << "Bruh\n";

	yaw += xoffset;
	pitch = Maths::clamp(pitch + yoffset, pitchMin, pitchMax);
	computeYawPitch();*/
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
	std::cout << "Yaw : " << yaw << " | Pitch : " << pitch << std::endl;
	setRotation(Quaternion::fromEuler(Maths::toRadians(yaw), 0.0f, 0.0f));
}
