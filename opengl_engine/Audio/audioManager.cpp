#include "audioManager.h"
#include <iostream>

bool AudioManager::Initialize()
{
	FMOD_RESULT result;

	//  intialize fmod debug
	result = FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR, FMOD_DEBUG_MODE_TTY);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD Init Error: Failed to initialize FMOD debug: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	//  create fmod studio system object
	result = FMOD::Studio::System::create(&system);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD Init Error: Failed to create FMOD studio system: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	//  initialize fmod studio system
	result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD Init Error: Failed to initialize FMOD studio system: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	//  retrieve the low-level system pointer
	result = system->getCoreSystem(&lowLevelSystem);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD Init Error: Failed to retrieve FMOD core system: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	return true;
}
