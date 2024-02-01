#pragma once
#include "collisionComponent.h"
#include <Events/event.h>


class RigidbodyComponent
{
public:
	RigidbodyComponent(CollisionComponent* collisionToAssociate, bool useCCD);
	~RigidbodyComponent();

	void associateCollision(CollisionComponent* collisionToAssociate);
	const CollisionComponent& getAssociatedCollision() const { return *associatedCollision; }

	void updatePosLastFrame();

	void setActivated(bool value);
	bool isActivated() const { return activated && associatedCollision; }

	void setUseCCD(bool value);
	bool getUseCCD() const { return ccd && !firstFrameCCD; }


	//  for physics manager
	bool registered{ false };

	Event<> onRigidbodyDelete;
	Event<> onCollisionIntersect;

private:
	CollisionComponent* associatedCollision{ nullptr };

	bool activated{ false };

	bool ccd{ false };
	bool firstFrameCCD{ true };
};

