#include "audioSound.h"
#include <FMod/fmod.hpp>
#include <FMod/fmod_errors.h>
#include <iostream>

AudioSound::AudioSound(FMOD::Sound* fmodSound_) : FModSound(fmodSound_)
{
	setupSpatialization();
}

AudioSound::AudioSound(const AudioSound& other) : FModSound(other.FModSound)
{
	setupSpatialization();
}

AudioSound& AudioSound::operator=(const AudioSound& other)
{
	FModSound = other.FModSound;
	setupSpatialization();
	return *this;
}

AudioSound::~AudioSound()
{
	//FModSound->release(); //  destructor is called when creating the Audio Sound, help me
}



bool AudioSound::isValid() const
{
	return FModSound != nullptr;
}

FMOD::Sound* AudioSound::getFMod() const
{
	return FModSound;
}

void AudioSound::releaseFMod()
{
	FModSound->release();
}

SpatializationMode AudioSound::getSpatialization() const
{
	return SoundSpatialization;
}

void AudioSound::setMinMaxDistance(float min, float max) const
{
	if (!isValid())
	{
		std::cout << "Audio Sound Error: Tried to set a min and max distance on an invalid sound.\n";
		return;
	}

	if (SoundSpatialization != SpatializationMode::Spatialization3D)
	{
		std::cout << "Audio Sound Error: Tried to set a min and max distance on a 2D sound.\n";
		return;
	}

	FMOD_RESULT result;
	result = FModSound->set3DMinMaxDistance(min, max);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Sound Error: Failed to set min and max distance. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
	}
}



void AudioSound::setupSpatialization()
{
	FMOD_MODE sound_mode;
	FMOD_RESULT result;
	result = FModSound->getMode(&sound_mode);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Sound Error: Failed to get the mode of the sound. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
	}

	if (sound_mode & FMOD_2D)
	{
		SoundSpatialization = SpatializationMode::Spatialization2D;
	}
	else if (sound_mode & FMOD_3D)
	{
		SoundSpatialization = SpatializationMode::Spatialization3D;
	}
	else
	{
		std::cout << "Audio Sound Error: Sound is neither 2D or 3D (should not be possible since 2D is default if unspecified).\n";
	}
}
