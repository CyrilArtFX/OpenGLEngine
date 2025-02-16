#pragma once


/** Physic Entity
* Interface for all objects that are related to physics.
* Currently collisions, rigidbodies and raycasts.
*/
class PhysicEntity
{
public:
	PhysicEntity(bool loadPersistent) : loadedPersistent(loadPersistent) {}
	PhysicEntity() = delete;

	//  is this physic entity loaded on the scene (deleted on scene change) or on the game (deleted only on engine closing)
	bool loadedPersistent{ false };
};