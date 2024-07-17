#pragma once
#include "collisionComponent.h"
#include "physicEntity.h"
#include <Events/event.h>
#include <Events/observer.h>


namespace Rigidbody
{
	const int MAX_BOUNCES = 5;
	const float SECURITY_DIST = 0.001f;
}


struct CollisionResponse
{
	Vector3 impactPoint{ Vector3::zero };
	Vector3 impactNormal{ Vector3::zero };
};


/** Rigidbody Component
* Will tests other colliders and react with physics if it is activated.
* If physics is not activated, will act as a static collision (even if it moves with velocity).
*/
class RigidbodyComponent : public PhysicEntity, public Observer
{
public:
	RigidbodyComponent(CollisionComponent* collisionToAssociate, bool activatePhysics);
	~RigidbodyComponent();

	void associateCollision(CollisionComponent* collisionToAssociate);
	inline const CollisionComponent& getAssociatedCollision() const { return *associatedCollision; }
	inline CollisionComponent& getAssociatedCollisionNonConst() { return *associatedCollision; }

	void updatePhysicsPreCollision(float dt);
	void updatePhysicsPostCollision(float dt);

	void setPhysicsActivated(bool value);
	inline bool isPhysicsActivated() const { return physicsActivated && associatedCollision; }

	void setUseGravity(bool value);
	inline bool getUseGravity() const { return useGravity; }

	void setStepHeight(float value);
	inline float getStepHeight() const { return stepHeight; }

	inline Vector3 getAnticipatedMovement() const { return movement; }
	inline Vector3 getAnticipatedGravityMovement() const { return gravityMovement; }
	void applyComputedMovement(const Vector3& computedMovement);
	void applyComputedGravityMovement(const Vector3& computedGravityMovement);

	bool checkStepMechanic(const CollisionComponent& collidedComp, const Vector3 aimedDestination, const Vector3 hitNormal, float& stepMovement) const;

	void setVelocity(const Vector3& value);
	void addVelocity(const Vector3& value);
	Vector3 getVelocity() const;

	void setGravityVelocity(const Vector3& value);
	void addGravityVelocity(const Vector3& value);
	Vector3 getGravityVelocity() const;

	void addVelocityOneFrame(const Vector3& value);

	inline bool isAssociatedCollisionValid() const { return associatedCollision; }

	inline bool isOnGround() const { return onGround && getUseGravity(); }

	void setTestChannels(std::vector<std::string> newTestChannels);
	void addTestChannel(std::string newTestChannel);
	std::vector<std::string> getTestChannels() const;

	void resetIntersected();


	//  for physics manager
	bool registered{ false };

	Event<> onRigidbodyDelete;
	Event<const CollisionResponse&> onCollisionRepulsed;



private:
	CollisionComponent* associatedCollision{ nullptr };

	bool physicsActivated{ false };

	float stepHeight{ 0.0f };

	Vector3 velocity{ Vector3::zero };
	Vector3 gravityVelocity{ Vector3::zero };
	Vector3 velocityOneFrame{ Vector3::zero };
	Vector3 movement{ Vector3::zero };
	Vector3 gravityMovement{ Vector3::zero };
	bool useGravity{ false };

	bool onGround{ false };
	bool groundedLastFrame{ false };


	bool firstFrame{ true };

	std::vector<std::string> testChannels;


	void onCollisionIntersected(RigidbodyComponent& other);
	void onCollision(const CollisionResponse& collisionResponse);
};

