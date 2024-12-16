#include "audioSound.h"
#include <ServiceLocator/locator.h>
#include <ServiceLocator/audio.h>
#include <FMod/fmod.hpp>
#include <FMod/fmod_errors.h>

AudioSound::AudioSound(FMOD::Sound* fmodSound_, const SoundSettings soundSettings) : FModSound(fmodSound_), Settings(soundSettings)
{
}

AudioSound::~AudioSound()
{
	releaseFMod();
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
	if (!isValid()) return;

	Audio& audio = Locator::getAudio();
	if (!audio.IsAudioSystemValid()) return;

	FModSound->release();
}

bool AudioSound::hasSetting(SoundSettings setting) const
{
	return Settings & setting;
}

void AudioSound::setMinMaxDistance(float min, float max) const
{
	if (!isValid())
	{
		Locator::getLog().LogMessage_Category("Audio Sound: Tried to set a min and max distances on an invalid sound.", LogCategory::Error);
		return;
	}

	if (!hasSetting(ACTIVATE_3D))
	{
		Locator::getLog().LogMessage_Category("Audio Sound: Tried to set a min and max distances on a 2D sound.", LogCategory::Error);
		return;
	}

	FMOD_RESULT result;
	result = FModSound->set3DMinMaxDistance(min, max);
	if (result != FMOD_OK)
	{
		Locator::getLog().LogMessage_Category("Audio Sound: Failed to set min and max distances. | Associated FMod Error: " + std::string(FMOD_ErrorString(result)), LogCategory::Error);
	}
}