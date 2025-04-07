#pragma once
#include <Rendering/cameraComponent.h>


/** Camera Lag Component
* An override of the camera component that supports camera lag.
* Currently support position lag, but not rotation lag.
*/
class CameraLagComponent : public CameraComponent
{
public:
	/** Setup the lag values for this Camera Lag Component. */
	void setupLag(const float& lagSpeed_, const float& lagMaxDist_);

	/** Instantly clear the lag and teleport the camera to the target position. */
	void teleport();

	void setLagSpeed(const float& lagSpeed_);
	void getLagMaxDist(const float& lagMaxDist_);

	Vector3 getCurrentLagEntityPos() const { return lagEntityPos; }
	float getLagSpeed() const { return lagSpeed; }
	float getLagMaxDist() const { return lagMaxDist; }

protected:
	virtual void init() override;
	virtual void update(float deltaTime) override;

	virtual void computeCameraVectors(bool computePos, bool computeDirections) override;

	Vector3 lagEntityPos{ Vector3::zero };

	float lagSpeed{ 0.0f };
	float lagMaxDist{ 0.0f };
};

