#pragma once
#include <Maths/Vector3.h>

class RigidbodyComponent;
class Box;

/**
* Static functions that will test collisions for rigidbodies.
*/
class CollisionTests
{
public:

	/**
	* Compute the movement by checking collisions for a physic activated rigidbody.
	* Algorithm used is Collide and Slide.
	* @param	rigidbody			Rigidbody to compute.
	* @param	gravityPass			Are we computing gravity?
	* @param	computedMovement	Movement to apply to the rigidbody. [OUT]
	* @return						True if the rigidbody encountered at least one collision.
	*/
	static bool RigidbodyCollideAndSlideAABB(const RigidbodyComponent& rigidbody, const bool gravityPass, Vector3& computedMovement);


private:

	/**
	* Core of the Collide and Slide algorithm, recursive function that will check the shape raycast.
	* @param	rigidbody			Rigidbody to use.
	* @param	boxAABB				Shape to use.
	* @param	startPos			Start of the raycast for this iteration.
	* @param	movement			Movement to check for this iteration.
	* @param	bounces				Iteration number.
	* @param	gravityPass			Are we computing gravity?
	* @param	computedPos			End of the raycast for this iteration. [OUT]
	* @return						True if this iteration's raycast encountered a collision.
	*/
	static bool CollideAndSlideAABB(const RigidbodyComponent& rigidbody, const Box& boxAABB, const Vector3 startPos, const Vector3 movement, const int bounces, const bool gravityPass, Vector3& computedPos);
};

