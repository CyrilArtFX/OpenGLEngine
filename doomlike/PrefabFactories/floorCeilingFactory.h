#pragma once
#include <ECS/entity.h>
#include <Maths/Vector2.h>

class EntityContainer;


namespace FloorCeilingFactory
{
	static Entity* CreateFloor(EntityContainer* entityContainer, const Vector3& position, const Vector2& scale, bool isWood, bool createCollision = true);
	static Entity* CreateCeiling(EntityContainer* entityContainer, const Vector3& position, const Vector2& scale, bool createCollision = true);

	static void SetupFloorCeilingAssets();
	static void ReleaseFloorCeilingAssets();
};

