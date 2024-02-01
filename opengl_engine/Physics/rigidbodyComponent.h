#pragma once
#include "collisionComponent.h"
#include <Events/event.h>


struct CollisionResponse
{
	Vector3 repulsion{ Vector3::zero };
};


/** Rigidbody Component
* Will tests other colliders and react with physics if it is activated.
* For now, CCD only works with position, not rotation or scale
* Also, intersection between two rigidbodies with CCD is not implemented
* For now, velocity doesn't reduce when colliding
*/
class RigidbodyComponent
{
public:
	RigidbodyComponent(CollisionComponent* collisionToAssociate, bool useCCD, bool activatePhysics);
	~RigidbodyComponent();

	void associateCollision(CollisionComponent* collisionToAssociate);
	const CollisionComponent& getAssociatedCollision() const { return *associatedCollision; }

	void updatePhysicsPreCollision(float dt);
	void updatePhysicsPostCollision(float dt);

	void updatePosLastFrame();

	void setPhysicsActivated(bool value);
	bool isPhysicsActivated() const { return physicsActivated && weight > 0.0f && associatedCollision; }

	void setWeigth(float value);
	float getWeight() const { return weight; }

	void setUseGravity(float value);
	bool getUseGravity() const { return useGravity; }

	void setVelocity(const Vector3& value);
	Vector3 getVelocity() const;

	bool isAssociatedCollisionValid() const { return associatedCollision; }

	void setUseCCD(bool value);
	bool getUseCCD() const { return ccd && !firstFrameCCD; }

	void resetIntersected();


	//  for physics manager
	bool registered{ false };

	Event<> onRigidbodyDelete;
	Event<> onCollisionIntersect;

	CollisionResponse currentResponse;

private:
	CollisionComponent* associatedCollision{ nullptr };

	bool physicsActivated{ false };
	float weight{ 1.0f };

	bool ccd{ false };
	bool firstFrameCCD{ true };

	Vector3 velocity{ Vector3::zero };
	bool useGravity{ false };
};

