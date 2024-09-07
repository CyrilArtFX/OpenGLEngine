#pragma once
#include <FMod/fmod.hpp>
#include <FMod/fmod_errors.h>

#include "audioSound.h"

#include <Maths/Vector3.h>

#include <string>
#include <unordered_map>


const int MAX_CHANNELS = 512;


enum class ChannelSpatialization : uint8_t
{
	Channel2D = 0,	//  For a channel that can play 2D sound
	Channel3D = 1	//  For a channel that can play 3D sound (movable in space)
};


class AudioManager
{
public:

	// ---------------------------------
	//  Core
	// ---------------------------------
	bool Initialize();
	void Quit();

	void Update();
	void UpdateListener(const Vector3 listenerPos, const Vector3 listenerUp, const Vector3 listenerForward);


	// ---------------------------------
	//  Engine pause
	// ---------------------------------
	void PauseAll();
	void ResumeAll();


	// ---------------------------------
	//  Load Sound
	// ---------------------------------
	AudioSound LoadSound(std::string soundFile, SoundSettings settings = 0);


	// ---------------------------------
	//  Global settings
	// ---------------------------------
	void SetGlobalVolume(const float volume); //  between 0 and 1
	float GetGlobalVolume();


	// ---------------------------------
	//  Audio Source
	// ---------------------------------
	std::uint32_t CreateAudioSourceGroup(ChannelSpatialization spatialization, const std::string name = "");
	void ReleaseAudioSourceGroup(const std::uint32_t index);

	void PlaySoundOnAudioSource(const std::uint32_t index, const AudioSound& sound, const int loop = 0); //  loop -1 = infinite, loop 0 = play only once
 	void StopAudioSource(const std::uint32_t index);

	void PauseAudioSource(const std::uint32_t index, const bool pause);
	bool GetAudioSourcePaused(const std::uint32_t index);

	void SetAudioSourceGroupVolume(const std::uint32_t index, const float volume); //  between 0 and 1
	float GetAudioSourceGroupVolume(const std::uint32_t index);

	void SetAudioSourceGroupPos(const std::uint32_t index, const Vector3 position);
	Vector3 GetAudioSourceGroupPos(const std::uint32_t index);


	// ---------------------------------
	//  Instant Play Sound
	// ---------------------------------
	void InstantPlaySound2D(const AudioSound& sound, const float volume = 1.0f, const int loop = 0);
	void InstantPlaySound3D(const AudioSound& sound, const Vector3 playPosition, const float volume = 1.0f, const int loop = 0);



private:
	FMOD::System* system{ nullptr };

	std::unordered_map<std::uint32_t, FMOD::ChannelGroup*> audioSourcesGroups;
	std::uint32_t audioSourcesGroupsID{ 0 };


	// ---------------------------------
	//  Helping Functions
	// ---------------------------------
	ChannelSpatialization GetGroupSpatialization(FMOD::ChannelGroup* group);
};

