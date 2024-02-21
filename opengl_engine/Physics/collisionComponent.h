#pragma once
#include "physicEntity.h"
#include <Objects/object.h>
#include "raycast.h"
#include "raycastLine.h"
#include "AABB/raycastAABB.h"

#include <Events/event.h>
#include <vector>

#include <Rendering/Model/mesh.h>

class Material;
class RigidbodyComponent;
struct CollisionResponse;


enum class CollisionType : uint8_t
{
	Null = 0,
	BoxAABB = 1
};


/** Collision Component
* Base class for every collision component
*/
class CollisionComponent : public PhysicEntity
{
public:
	virtual ~CollisionComponent();

	inline CollisionType getCollisionType() const { return collisionType; }

	void setAssociatedObject(Object* newObject);
	inline const Object* getAssociatedObject() const { return associatedObject; }

	bool resolvePoint(const Vector3& point) const;
	bool resolveLineRaycast(const Ray& raycast, RaycastHitInfos& outHitInfos, const std::vector<std::string> testChannels) const;
	bool resolveAABBRaycast(const Box& raycast, const std::vector<std::string> testChannels) const;
	bool resolveCollision(const CollisionComponent& otherCol, const std::vector<std::string> testChannels) const;
	bool resolveRigidbody(const RigidbodyComponent& rigidbody, CollisionResponse& outResponse) const;
	bool resolveRigidbodySelf(const RigidbodyComponent& rigidbody, const RigidbodyComponent& selfRigidbody) const; //  doesn't have response since body/body doesn't compute repulsion (yet)

	void drawDebug(Material& debugMaterial) const;

	virtual const Matrix4 getModelMatrix() const;

	void resetIntersected();

	//  for physics manager
	void forceIntersected() const;
	inline bool getIntersected() const { return intersectedLastFrame; }

	void addPosition(const Vector3& posToAdd);

	void setCollisionChannel(std::string newCollisionChannel);
	std::string getCollisionChannel() const { return collisionChannel; }


	//  for physics manager
	bool registered{ false };


	
	Event<> onCollisionDelete;
	mutable Event<RaycastType, const Vector3&> onRaycastIntersect;
	Event<RigidbodyComponent&> onCollisionIntersect;



	bool channelTest(const std::vector<std::string> testChannels) const;


protected:
	CollisionComponent(CollisionType collisionType_, Object* associatedObject_, Mesh* debugMesh_, bool loadPersistent_, std::string collisionChannel_);

	virtual bool resolvePointIntersection(const Vector3& point) const = 0;
	virtual bool resolveLineRaycastIntersection(const Ray& raycast, RaycastHitInfos& outHitInfos) const = 0;
	virtual bool resolveAABBRaycastIntersection(const Box& raycast) const = 0;
	virtual bool resolveCollisionIntersection(const CollisionComponent& otherCol) const = 0;
	virtual bool resolveRigidbodyIntersection(const RigidbodyComponent& rigidbody, CollisionResponse& outResponse) const = 0;
	virtual bool resolveRigidbodySelfIntersection(const RigidbodyComponent& rigidbody, const RigidbodyComponent& selfRigidbody) const = 0;

	virtual void drawDebugMesh(Material& debugMaterial) const = 0;


	CollisionType collisionType{ CollisionType::Null };
	Object* associatedObject{ nullptr };


	//  for debug drawing
	Mesh* debugMesh{ nullptr };

private:
	mutable bool intersectedLastFrame{ false };

	std::string collisionChannel{ "" };
};