#pragma once
#include <FMod/fmod_studio.hpp>
#include <FMod/fmod_errors.h>

class AudioManager
{
public:
	bool Initialize();

private:
	FMOD::Studio::System* system{ nullptr };
	FMOD::System* lowLevelSystem{ nullptr };
};

