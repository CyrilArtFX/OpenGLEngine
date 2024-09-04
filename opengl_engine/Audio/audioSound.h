#pragma once
#include <stdint.h>

namespace FMOD //  avoid including "fmod.hpp"
{
	class Sound;
}

enum class SpatializationMode : uint8_t
{
	Spatialization2D = 0, //  2D sound
	Spatialization3D = 1 //  3D sound movable in space
};

enum class LoadingMode : uint8_t
{
	LoadSample = 0, //  Load entire file in memory (great for small sound file)
	LoadStream = 1 //  Stream sound from file at runtime (great for big sound file)
};

class AudioSound
{
public:
	AudioSound() {} //  can't delete default constructor, asset manager map of this type need it
	AudioSound(FMOD::Sound* fmodSound_);
	AudioSound(const AudioSound& other);
	AudioSound& operator=(const AudioSound& other);
	~AudioSound();

	bool isValid() const;
	FMOD::Sound* getFMod() const;
	void releaseFMod();

	SpatializationMode getSpatialization() const;

	//  distances for sound fading
	void setMinMaxDistance(float min, float max) const;

private:
	FMOD::Sound* FModSound{ nullptr };
	SpatializationMode SoundSpatialization{ SpatializationMode::Spatialization2D };

	void setupSpatialization();
};

