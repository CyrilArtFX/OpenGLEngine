#pragma once
#include <ECS/entity.h>

class EntityContainer;


namespace LampFactory
{
	static Entity* CreateLamp(EntityContainer* entityContainer, const Vector3& position, bool isCeiling, bool startOff = false);

	static void SetupLampAssets();
	static void ReleaseLampAssets();
}

