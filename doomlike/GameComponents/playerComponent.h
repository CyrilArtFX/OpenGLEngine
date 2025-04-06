#pragma once
#include <ECS/component.h>
#include <Events/observer.h>
#include <Objects/transform.h>


/**
* This component is responsible of the rigidbody, the movement and the camera.
* It automatically create the needed components on its entity.
*/
class PlayerComponent : public Component, public Observer
{
public:
	void setupPlayer(float camHeight_, float moveSpeed_, float jumpForce_, float stepHeight_);

	void respawn(const Transform& respawnTransform);
	Vector3 getCamPosition() const;

	void onCollision(const struct CollisionResponse& collisionResponse);


protected:
	void init() override;
	void update(float deltaTime) override;

private:
	Entity* entity{ nullptr };
	std::shared_ptr<class CameraLagComponent> camera;
	std::shared_ptr<class BoxAABBColComp> collision;
	std::shared_ptr<class RigidbodyComponent> rigidbody;
	std::shared_ptr<class AudioSourceComponent> feetSoundSource;

	float camHeight{ 0.0f };
	float moveSpeed{ 0.0f };
	float jumpForce{ 0.0f };

	float feetSoundTimer{ 0.0f };
	bool feetSoundAlternance{ false };
	bool onGroundLastFrame{ true };

	const float camSensitivity{ 0.08f };
	const float camLagSpeed{ 8.8f };
	const float camLagMaxDist{ 0.7f };
};

