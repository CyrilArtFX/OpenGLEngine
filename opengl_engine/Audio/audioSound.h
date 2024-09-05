#pragma once
#include <stdint.h>

namespace FMOD //  avoid including "fmod.hpp"
{
	class Sound;
}


//  unsigned char cause we don't need more than 8 bits
typedef unsigned char SoundSettings;
#define ACTIVATE_3D		1 << 0	//  Make this sound a 3D sound, capable of being played at a certain position in the world
#define ACTIVATE_STREAM	1 << 1	//  Make the sound streaming from its file at runtime (use on big sound files)
#define ACTIVATE_LOOP	1 << 2	//  Enable loop playing on this sound


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

