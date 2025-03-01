#pragma once
#include <ECS/component.h>
#include <Physics/collisionComponent.h>

#include <Maths/Vector3.h>

#include <Events/event.h>
#include <Events/observer.h>

#include <memory>
#include <vector>
#include <string>


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
* Component that can be associated with a Collision Component on an Entity.
* If the Rigidbody have physics activated, it will have gravity and will test and be blocked by other collisions.
* If physics is not activated, it will act as a static collision and won't test other collisions but will still be able to move with velocity.
* Repulsion between two physics activated Rigidbodies is not implemented for the moment, but the collision detection (trigger) will still happen.
*/
class RigidbodyComponent : public Component, public Observer, public std::enable_shared_from_this<RigidbodyComponent>
{
	//  categories de fonction:
	//  - associated collision
	//  - update physics and apply movements (physics manager only?)
	//  - parameters (set and get)
	//  - velocity (with velocity one frame)
	//  - gravity velocity
	//  - test channels
	//  - others (is on ground & step mechanic)



// ----------------------------------------------------------
//  Associated Collision
// ----------------------------------------------------------
public:
	/**
	* Set the associated collision of this rigidbody.
	* @param	collisionToAssociate	The collision that this rigidbody must manage.
	*/
	void associateCollision(std::weak_ptr<CollisionComponent> collisionToAssociate);

	/**
	* Know if the collision managed by this rigidbody is valid, ie. if this rigidbody is valid.
	* @return	True if this rigidbody manage a valid collision.
	*/
	bool isAssociatedCollisionValid() const;

	/**
	* Get a const reference to the collision managed by this rigidbody.
	* @return	The const reference to the associated collision.
	*/
	const CollisionComponent& getAssociatedCollision() const;

	/**
	* Get a non-const reference to the collision managed by this rigidbody.
	* @return	The non-const reference to the associated collision.
	*/
	CollisionComponent& getAssociatedCollisionNonConst();


// ----------------------------------------------------------
//  Rigidbody Parameters
// ----------------------------------------------------------
public:
	/** Set this Rigidbody as physics activated or not. Physics activated Rigidbodies will test collisions. */
	void setPhysicsActivated(bool value);

	/** Set this Rigidbody to use gravity or not. */
	void setUseGravity(bool value);

	/** Set the step height of this Rigidbody, to automatically step over collisions when moving with velocity (only works if physics is activated). */
	void setStepHeight(float value);


	/** Know if this Rigidbody is physics activated. Note that if it doesn't manage a valid collision, it will return false. */
	bool isPhysicsActivated() const;

	/** Get the value of 'use gravity' of this Rigidbody. */
	bool getUseGravity() const;

	/** Get the value of 'step height' of this Rigidbody. */
	float getStepHeight() const;


// ----------------------------------------------------------
//  Velocity
// ----------------------------------------------------------
public:
	/**
	* Set the velocity of this Rigidbody.
	* @param	value	The velocity value to set.
	*/
	void setVelocity(const Vector3& value);

	/**
	* Increment the velocity of this Rigidbody.
	* @param	value	The velocity value to add.
	*/
	void addVelocity(const Vector3& value);

	/**
	* Increment the velocity of this Rigidbody, only for one frame.
	* @param	value	The velocity value to add for one frame.
	*/
	void addVelocityOneFrame(const Vector3& value);

	/**
	* Get the velocity of this Rigidbody.
	* @return	The velocity of this Rigidbody.
	*/
	Vector3 getVelocity() const;

	/**
	* Get the movement that is anticipated by this Rigidbody for the current frame.
	* Note that this function will work only during the Physics part of the update.
	* This function is mainly useful for the collision tests of the Physics computations.
	* @return	The anticipated movement for the current frame.
	*/
	Vector3 getAnticipatedMovement() const;


// ----------------------------------------------------------
//  Gravity Velocity
// ----------------------------------------------------------
public:
	/**
	* Set the gravity velocity of this Rigidbody.
	* @param	value	The gravity velocity value to set.
	*/
	void setGravityVelocity(const Vector3& value);

	/**
	* Increment the gravity velocity of this Rigidbody.
	* @param	value	The gravity velocity value to add.
	*/
	void addGravityVelocity(const Vector3& value);

	/**
	* Get the gravity velocity of this Rigidbody.
	* @return	The gravity velocity of this Rigidbody.
	*/
	Vector3 getGravityVelocity() const;

	/**
	* Get the gravity movement that is anticipated by this Rigidbody for the current frame.
	* Note that this function will work only during the Physics part of the update.
	* This function is mainly useful for the collision tests of the Physics computations.
	* @return	The anticipated gravity movement for the current frame.
	*/
	Vector3 getAnticipatedGravityMovement() const;


// ----------------------------------------------------------
//  Other Rigidbody Functions
// ----------------------------------------------------------
public:
	/**
	* Check the step mechanic on a collision for this Rigidbody.
	* The step mechanic allows a physics activated Rigidbody to step over collisions that are low enough.
	* @param	collidedComp		The collision component to compute the step mechanic on.
	* @param	aimedDestination	The position that this rigidbody want to reach but blocked by the collision component.
	* @param	hitNormal			The normal vector of the surface hit on the collision component.
	* @param	stepMovement		[OUT] The computed vertical movement needed to reach the aimed destination on top of the collision component.
	* @return						True if the step mechanic is valid for this situation, false otherwise.
	*/
	bool checkStepMechanic(const CollisionComponent& collidedComp, const Vector3 aimedDestination, const Vector3 hitNormal, float& stepMovement) const;

	/**
	* Know if this Rigidbody is on the ground.
	* @return	True if this Rigidbody uses gravity and if it is on the ground.
	*/
	bool isOnGround() const;


// ----------------------------------------------------------
//  Rigibody Test Channels
// ----------------------------------------------------------
public:

	void setTestChannels(std::vector<std::string> newTestChannels);
	void addTestChannel(std::string newTestChannel);
	std::vector<std::string> getTestChannels() const;





	void updatePhysicsPreCollision(float dt);
	void updatePhysicsPostCollision(float dt);
	void applyComputedMovement(const Vector3& computedMovement);
	void applyComputedGravityMovement(const Vector3& computedGravityMovement);








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


	void onCollisionIntersected(RigidbodyComponent& other, const CollisionResponse& collisionResponse);
	void onCollision(const CollisionResponse& collisionResponse);
};

