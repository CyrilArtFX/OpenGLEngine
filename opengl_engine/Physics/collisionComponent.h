#pragma once
#include <Objects/transform.h>
#include "raycast.h"

#include <Events/event.h>

#include <Rendering/Model/mesh.h>

class Material;


enum class CollisionType : uint8_t
{
	Null = 0,
	BoxAABB = 1
};


/** Collision Component
* Base class for every collision component
* For now, CCD only works with position, not rotation or scale
* Also, intersection between two collisions with CCD is not implemented
*/
class CollisionComponent
{
public:
	virtual ~CollisionComponent();

	inline CollisionType getCollisionType() const { return collisionType; }

	void setAssociatedTransform(const Transform* newTransform);

	bool resolvePoint(const Vector3& point) const;
	bool resolveRaycast(const Ray& raycast, RaycastHitInfos& outHitInfos) const;
	bool resolveCollision(const CollisionComponent& otherCol) const;

	void drawDebug(Material& debugMaterial) const;

	virtual const Matrix4 getModelMatrix() const;

	void updateCollisionBeforeTests();
	void updateCollisionAfterTests();

	//  for physics manager
	void forceIntersected() const;
	inline bool getIntersected() const { return intersectedLastFrame; }

	void setCCD(bool ccd);
	inline bool getUseCCD() const { return useCCD && !firstFrame; }


	//  for physics manager
	bool registered{ false };


	
	Event<> onCollisionDelete;
	mutable Event<const Vector3&> onRaycastIntersect;
	mutable Event<> onCollisionIntersect;


protected:
	CollisionComponent(CollisionType collisionType_, const Transform* associatedTransform_, Mesh* debugMesh_);

	virtual bool resolvePointIntersection(const Vector3& point) const = 0;
	virtual bool resolveRaycastIntersection(const Ray& raycast, RaycastHitInfos& outHitInfos) const = 0;
	virtual bool resolveCollisionIntersection(const CollisionComponent& otherCol) const = 0;

	virtual void drawDebugMesh(Material& debugMaterial) const = 0;


	inline Vector3 getLastFramePos() const { return posLastFrame; }


	CollisionType collisionType{ CollisionType::Null };
	const Transform* associatedTransform{ nullptr };


	//  for debug drawing
	Mesh* debugMesh{ nullptr };

private:
	mutable bool intersectedLastFrame{ false };

	//  for CCD
	bool useCCD{ false };
	Vector3 posLastFrame{ Vector3::zero };
	bool firstFrame{ true };
};