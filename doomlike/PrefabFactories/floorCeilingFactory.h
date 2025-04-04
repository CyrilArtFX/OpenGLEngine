#pragma once
#include <ECS/entity.h>
#include <Maths/Vector2.h>

class EntityContainer;


namespace FloorCeilingFactory
{
	Entity* CreateFloor(EntityContainer* entityContainer, const Vector3& position, const Vector2& scale, bool isWood, bool createCollision = true);
	Entity* CreateCeiling(EntityContainer* entityContainer, const Vector3& position, const Vector2& scale, bool createCollision = true);

	void SetupFloorCeilingAssets();
	void ReleaseFloorCeilingAssets();
};

// TODO: the definition in a .cpp of static function declared in a .h seems to not work, see if it is possible to avoid having everything 