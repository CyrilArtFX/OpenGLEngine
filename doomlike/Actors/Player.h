#pragma once
#include "bullet.h"

#include <Rendering/camera.h>
#include <Objects/transform.h>

#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>

#include <Audio/audioSourceComponent.h>
#include <Rendering/Hud/spriteRendererComponent.h>
#include <Rendering/Text/textRendererComponent.h>

#include <GameLogic/playerSpawnPoint.h>

#include <Events/observer.h>

#include <vector>


class Player : public Object, public Observer
{
public:
	Player();
	void setup(float height, float speed, float jump, float stepHeight);

	void update(float dt);

	void unload();

	//  set rotation to spawn point not working because of camera
	void respawn(PlayerSpawnPoint& spawnPoint);


	void onRigidbodyDeleted();

	void onCollision(const CollisionResponse& collisionResponse);

	Vector3 getEyePosition() const;


	Camera& getCamera() { return camera; }

private:
	Camera camera;

	float camHeight{ 0.0f };
	float moveSpeed{ 0.0f };
	float jumpForce{ 0.0f };
	
	Vector3 camPos{ Vector3::zero };
	float camSpeed{ 8.8f };
	float camMaxDist{ 0.7f };

	//  bullets
	std::vector<std::unique_ptr<Bullet>> bullets;
	float shootVelocity{ 15.0f };
	float bulletLifeTime{ 3.0f };
	int ammoCount{ 5 };
	float reloadTimer{ 0.0f };

	float feetSoundTimer{ 0.0f };
	bool feetSoundAlternance{ false };
	bool onGroundLastFrame{ true };

	Object gunObject;

	RigidbodyComponent* rigidbody;
	AudioSourceComponent* audioSource;
	SpriteRendererComponent* crosshairSprite;
	TextRendererComponent* ammoText;


	void shootBullet();
	void startReload();
	void reload(float dt);
};

