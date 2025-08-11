#pragma once
#include <ECS/component.h>
#include <Maths/Vector3.h>


/**
* Add this component to an entity to make it a moving platform.
* This component add the collision, the rigidbody and the audio component, but not the model renderer.
*/
class MovingPlatformComponent : public Component
{
public:
	void setupMovingPlatform(const Vector3& pointA_, const Vector3& pointB_, const float movementSpeed_, const float waitTime_ = 0.0f, const bool debug_ = false);

	void pauseMovement();
	void resumeMovement();

protected:
	void init() override;
	void exit() override;
	void update(float deltaTime) override;

	virtual void updateDebug(float deltaTime);

private:
	std::shared_ptr<class BoxAABBColComp> collision;
	std::shared_ptr<class RigidbodyComponent> rigidbody;
	std::shared_ptr<class AudioSourceComponent> audioSource;

	Vector3 pointA{ Vector3::zero };
	Vector3 pointB{ Vector3::zero };
	float timeAtoB{ 0.0f };
	float waitTime{ 0.0f };

	float timer{ 0.0f };
	float waitTimer{ 0.0f };
	bool reverse{ false };
	bool waiting{ false };
	bool paused{ false };

	bool debug{ false };
};

