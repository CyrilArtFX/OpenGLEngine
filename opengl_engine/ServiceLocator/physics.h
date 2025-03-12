#pragma once
#include <Physics/raycast.h>

class CollisionComponent;
class RigidbodyComponent;
struct Vector3;
class Box;
class Material;


/**
* The Physics Service class (the virtual class provided by the Locator).
*/
class Physics
{
public:
	virtual ~Physics() {}

	/**
	* Register a Collision Component in the physics engine.
	* @param	colComp		Collision Component to register.
	*/
	virtual void RegisterCollision(CollisionComponent* colComp) = 0;

	/**
	* Unregister a Collision Component from the physics engine.
	* @param	colComp		Collision Component to unregister.
	*/
	virtual void UnregisterCollision(CollisionComponent* colComp) = 0;


	/**
	* Register a Rigidbody Component in the physics engine.
	* @param	rigidbodyComp	Rigidbody Component to register.
	*/
	virtual void RegisterRigidbody(RigidbodyComponent* rigidbodyComp) = 0;

	/**
	* Unregister a Rigidbody Component from the physics engine.
	* @param	rigidbodyComp	Rigidbody Component to unregister.
	*/
	virtual void UnregisterRigidbody(RigidbodyComponent* rigidbodyComp) = 0;



	/**
	* Creates a line-shaped raycast between two points.
	* @param	start			Start point of the raycast (world coordinates).
	* @param	end				End point of the raycast (world coordinates).
	* @param	testChannels	Collision channels the raycast will test.
	* @param	outHitInfos		Informations on the closest encountered collision.
	* @param	drawDebugTime	Duration of the raycast debug draw. (0 = no draw debug, negative = infinite draw debug).
	* @param	createOnScene	Is the raycast registered on the scene (delete if scene change) or on the game (persist when changing scene).
	* @return					True if at least one collision intersect the line raycast.
	*/
	virtual bool LineRaycast(const Vector3& start, const Vector3& end, const std::vector<std::string> testChannels = {}, RaycastHitInfos& outHitInfos = RaycastHitInfos::defaultInfos, float drawDebugTime = 5.0f, bool createOnScene = true) = 0;

	/**
	* Creates an AABB box-shaped raycast at a location.
	* @param	location		Location of the raycast (world coordinates).
	* @param	aabbBox			Box shape of the raycast.
	* @param	testChannels	Collision channels the raycast will test.
	* @param	drawDebugTime	Duration of the raycast debug draw. (0 = no draw debug, negative = infinite draw debug).
	* @param	createOnScene	Is the raycast registered on the scene (delete if scene change) or on the game (persist when changing scene).
	* @return					True if at least one collision intersect the aabb box raycast.
	*/
	virtual bool AABBRaycast(const Vector3& location, const Box& aabbBox, const std::vector<std::string> testChannels = {}, float drawDebugTime = 5.0f, bool createOnScene = true) = 0;

	/**
	* Sweep an AABB box-shaped raycast between two points.
	* @param	start				Start point of the sweep (world coordinates).
	* @param	end					End point of the sweep (world coordinates).
	* @param	aabbBox				Box shape of the raycast.
	* @param	testChannels		Collision channels the raycast will test.
	* @param	outHitInfos			Informations on the closest encountered collision.
	* @param	drawDebugTime		Duration of the raycast debug draw. (0 = no draw debug, negative = infinite draw debug).
	* @param	createOnScene		Is the raycast registered on the scene (delete if scene change) or on the game (persist when changing scene).
	* @param	forCollisionTest	Does this function is used by the collision test algorithm?
	* @return						True if at least one collision intersect the sweeped aabb box raycast.
	*/
	virtual bool AABBSweepRaycast(const Vector3& start, const Vector3& end, const Box& aabbBox, const std::vector<std::string> testChannels = {}, RaycastHitInfos& outHitInfos = RaycastHitInfos::defaultInfos, float drawDebugTime = 5.0f, bool createOnScene = true, bool forCollisionTest = false) = 0;


	/**
	* Retrieve the gravity strength.
	* @return	Gravity value.
	*/
	virtual float GetGravityValue() = 0;


	/**
	* Set if the physics can log infos.
	* @param	enable		Enable state of info logging.
	*/
	virtual void SetEnableInfoLogs(bool enable) = 0;


private:
	friend class Engine;
	virtual void InitialisePhysics() = 0;
	virtual void UpdatePhysics(float dt) = 0;

	friend class RendererOpenGL;
	virtual void DrawCollisionsDebug(Material& debugMaterial) = 0;

	friend class Scene;
	virtual void ClearRaycastOnSceneUnload(bool exitGame) = 0;
};