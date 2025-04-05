#pragma once
#include <Objects/transform.h>

class PlayerSpawnPoint
{
public:
	const Transform& getSpawnPoint() { return *spawnPoint; }

	Transform* spawnPoint{ nullptr };
};

