#pragma once
#include "physicEntity.h"
#include <Objects/object.h>
#include "raycast.h"
#include "raycastLine.h"
#include "AABB/raycastAABB.h"
#include <Maths/Geometry/box.h>
#include <Audio/audioUtils.h>

#include <Events/event.h>
#include <Events/observer.h>
#include <vector>

#include <Rendering/Model/mesh.h>

class Material;
class RigidbodyComponent;


enum class CollisionShape : uint8_t
{
	Null = 0,
	BoxAABB = 1
};

enum class CollisionType : uint8_t
{
	Solid = 0,
	Trigger = 1
};




/** Collision Component
* Base class for every collision component
*/
class CollisionComponent : public PhysicEntity, public Observer
{
public:
	virtual ~CollisionComponent();

	inline CollisionShape getCollisionShape() const { return collisionShape; }
	inline CollisionType getCollisionType() const { return collisionType; }

	void setAssociatedObject(Object* newObject);
	inline const Object* getAssociatedObject() const { return associatedObject; }

	bool resolvePoint(const Vector3& point) const;
	bool resolveLineRaycast(const Ray& raycast, RaycastHitInfos& outHitInfos, const std::vector<std::string> testChannels) const;
	bool resolveAABBRaycast(const Box& raycast, const std::vector<std::string> testChannels) const;
	bool resolveAABBSweepRaycast(const Ray& raycast, const Box& boxRaycast, RaycastHitInfos& outHitInfos, const std::vector<std::string> testChannels, bool forCollisionTest = false) const;

	void drawDebug(Material& debugMaterial) const;

	virtual const Matrix4 getModelMatrix() const;

	virtual Vector3 getCenterDownPos() const { return Vector3::zero; }
	virtual Box getEncapsulatingBox() const { return Box::zero; }

	void resetIntersected();

	//  for physics manager
	void forceIntersected() const;
	inline bool getIntersected() const { return intersectedLastFrame; }

	void addPosition(const Vector3& posToAdd);

	void setCollisionChannel(std::string newCollisionChannel);
	std::string getCollisionChannel() const { return collisionChannel; }

	bool usedByRigidbody() const;
	RigidbodyComponent* getOwningRigidbody() const;

	virtual void setupAudioCollision(const AudioCollisionOcclusion& audioCollisionType) {}



	//  for physics manager
	bool registered{ false };


	
	Event<> onCollisionDelete;
	mutable Event<RaycastType, const Vector3&> onRaycastIntersect;
	mutable Event<RigidbodyComponent&, const struct CollisionResponse&> onCollisionIntersect;
	mutable Event<RigidbodyComponent&> onTriggerEnter;



	bool channelTest(const std::vector<std::string> testChannels) const;


protected:
	CollisionComponent(CollisionShape collisionShape_, CollisionType collisionType_, Object* associatedObject_, Mesh* debugMesh_, bool loadPersistent_, std::string collisionChannel_);

	virtual bool resolvePointIntersection(const Vector3& point) const = 0;
	virtual bool resolveLineRaycastIntersection(const Ray& raycast, RaycastHitInfos& outHitInfos) const = 0;
	virtual bool resolveAABBRaycastIntersection(const Box& raycast) const = 0;
	virtual bool resolveAABBSweepRaycastIntersection(const Ray& raycast, const Box& boxRaycast, RaycastHitInfos& outHitInfos, bool forCollisionTest) const = 0;

	virtual void drawDebugMesh(Material& debugMaterial) const = 0;

	virtual void onAssociatedTransformUpdated() {}


	CollisionShape collisionShape{ CollisionShape::Null };
	CollisionType collisionType{ CollisionType::Solid };
	Object* associatedObject{ nullptr };

	bool isAudioCollision{ false };
	std::uint32_t audioCollisionIndex{ 0 };


	//  for debug drawing
	Mesh* debugMesh{ nullptr };

private:
	mutable bool intersectedLastFrame{ false };

	std::string collisionChannel{ "" };

	friend class RigidbodyComponent;

	void setRigidbody(RigidbodyComponent* rigidbody);
	RigidbodyComponent* owningBody;
};