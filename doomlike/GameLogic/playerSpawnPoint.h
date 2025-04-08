#pragma once
#include <Core/transform.h>

class PlayerSpawnPoint
{
public:
	const Transform& getSpawnPoint() { return *spawnPoint; }

	Transform* spawnPoint{ nullptr };
};

