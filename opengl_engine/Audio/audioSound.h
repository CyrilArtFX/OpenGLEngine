#pragma once
#include "audioUtils.h"
#include <stdint.h>

namespace FMOD //  avoid including "fmod.hpp"
{
	class Sound;
}

class AudioSound
{
public:
	AudioSound() {} //  can't delete default constructor, asset manager map of this type need it
	AudioSound(FMOD::Sound* fmodSound_, SoundSettings soundSettings);
	AudioSound(const AudioSound& other);
	AudioSound& operator=(const AudioSound& other);
	~AudioSound();

	bool isValid() const;
	FMOD::Sound* getFMod() const;
	void releaseFMod();

	bool hasSetting(SoundSettings setting) const;

	//  distances for sound fading
	void setMinMaxDistance(float min, float max) const;

private:
	FMOD::Sound* FModSound{ nullptr };
	SoundSettings Settings{ 0 };
};

