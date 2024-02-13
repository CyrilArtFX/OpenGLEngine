#pragma once
#include "collisionComponent.h"
#include <Events/event.h>


struct CollisionResponse
{
	Vector3 repulsion{ Vector3::zero };
	Vector3 impactPoint{ Vector3::zero };
	Vector3 impactNormal{ Vector3::zero };
};


/** Rigidbody Component
* Will tests other colliders and react with physics if it is activated.
* For now, CCD only works with position, not rotation or scale
* Also, intersection between two rigidbodies with CCD is not implemented
*/
class RigidbodyComponent
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
	inline bool isPhysicsActivated() const { return physicsActivated && weight > 0.0f && associatedCollision; }

	void setWeigth(float value);
	inline float getWeight() const { return weight; }

	void setUseGravity(float value);
	inline bool getUseGravity() const { return useGravity; }

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
	Event<const CollisionResponse&> onCollisionIntersect;

private:
	CollisionComponent* associatedCollision{ nullptr };

	bool physicsActivated{ false };
	float weight{ 1.0f };

	bool ccd{ false };

	Vector3 velocity{ Vector3::zero };
	Vector3 movement{ Vector3::zero };
	bool useGravity{ false };
};

