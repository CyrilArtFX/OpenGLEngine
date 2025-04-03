#pragma once
#include <ECS/entity.h>

class EntityContainer;


namespace StairFactory
{
	enum class StairFacingDirection : uint8_t
	{
		StairFacingPositiveX = 0,
		StairFacingNegativeX = 1,
		StairFacingPositiveZ = 2,
		StairFacingNegativeZ = 3
	};

	static Entity* CreateStair(EntityContainer* entityContainer, StairFacingDirection facingDirection, const Vector3& position);

	static void SetupStairAssets();
	static void ReleaseStairAssets();
}