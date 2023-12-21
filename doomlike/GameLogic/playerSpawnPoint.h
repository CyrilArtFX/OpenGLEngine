#pragma once

#include <Maths/vector3.h>
#include <Maths/quaternion.h>

class PlayerSpawnPoint
{
public:
	virtual ~PlayerSpawnPoint() {}

	Vector3 spawnPosition{ Vector3::zero };
	Quaternion spawnRotation{ Quaternion::identity };
};

