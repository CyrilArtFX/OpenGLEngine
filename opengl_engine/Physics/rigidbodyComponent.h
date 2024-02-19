#pragma once
#include "collisionComponent.h"
#include "physicEntity.h"
#include <Events/event.h>


struct CollisionResponse
{
	Vector3 repulsion{ Vector3::zero };
	Vector3 impactPoint{ Vector3::zero };
	Vector3 impactNormal{ Vector3::zero };
};


/** Rigidbody Component
* Will tests other colliders and react with physics if it is activated.
* If physics is not activated, will act as a static collision (even if it moves with velocity).
* CCD works with the rigidbody velocity and won't have effect if physics is not activated.
* Step mechanic only works with static collisions (or with rigidbodies with physics not activated that act as statif collisions).
* Collisions between physics activated rigidbodies are not implemented. They will call the onCollision event, but won't compute repulsion.
* Rigidbody weight cannot be inferior or equal to 0 (and weight currently has no effect as bodies collisions doesn't work).
*/
class RigidbodyComponent : public PhysicEntity
{
public:
	RigidbodyComponent(CollisionComponent* collisionToAssociate, bool useCCD, bool activatePhysics);
	~RigidbodyComponent();

	void associateCollision(CollisionComponent* collisionToAssociate);
	inline const CollisionComponent& getAssociatedCollision() const { return *associatedCollision; }
	inline CollisionComponent& getAssociatedCollisionNonConst() { return *associatedCollision; }

	void updatePhysicsPreCollision(float dt);
	void updatePhysicsPostCollision(float dt);

	void setPhysicsActivated(bool value);
	inline bool isPhysicsActivated() const { return physicsActivated && associatedCollision; }

	void setWeigth(float value);
	inline float getWeight() const { return weight; }

	void setUseGravity(float value);
	inline bool getUseGravity() const { return useGravity; }

	void setStepHeight(float value);
	inline float getStepHeight() const { return stepHeight; }

	inline Vector3 getAnticipatedMovement() const { return movement; }
	void computeRepulsion(const Vector3& repulsion);

	void setVelocity(const Vector3& value);
	Vector3 getVelocity() const;

	inline bool isAssociatedCollisionValid() const { return associatedCollision; }

	void setUseCCD(bool value);
	inline bool getUseCCD() const { return ccd; }

	void resetIntersected();


	//  for physics manager
	bool registered{ false };

	Event<> onRigidbodyDelete;
	Event<const CollisionResponse&> onCollisionRepulsed;

private:
	CollisionComponent* associatedCollision{ nullptr };

	bool physicsActivated{ false };
	float weight{ 1.0f };

	bool ccd{ false };

	float stepHeight{ 0.0f };

	Vector3 velocity{ Vector3::zero };
	Vector3 movement{ Vector3::zero };
	bool useGravity{ false };


	bool firstFrame{ true };
};

