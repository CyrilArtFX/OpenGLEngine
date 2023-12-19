#pragma once

#include <glad/glad.h>
#include <Objects/transform.h>


enum Camera_Movement
{
	Forward,
	Backward,
	Left,
	Right,
	Up,
	Down
};


//  default values
const Vector3 POSITION = Vector3::zero;
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

const float PITCH_MIN = -89.0f;
const float PITCH_MAX = 89.0f;
const float FOV_MIN = 1.0f;
const float FOV_MAX = 45.0f;


class Camera : public Transform
{
public:
	Camera(Vector3 position_ = POSITION, float yaw_ = YAW, float pitch_ = PITCH, float fov_ = FOV);
	Camera() = delete;
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	Matrix4 getViewMatrix();
	
	void freecamKeyboard(Camera_Movement direction, float deltaTime);
	void freecamMouseMovement(float xoffset, float yoffset);
	void freecamMouseScroll(float yoffset);

	Vector3 getFlatFront();

	void setSpeed(float newSpeed);
	void setSensitivity(float newSensitivity);

	void setPitchClamp(float min, float max);
	void setFovClamp(float min, float max);

	float getFov() { return fov; }

	void copyCameraTransform(Camera& camera);


private:
	void computeYawPitch();

	float yaw;
	float pitch;

	float camSpeed;
	float sensitivity;
	float fov;

	float pitchMin;
	float pitchMax;
	float fovMin;
	float fovMax;
};

