#pragma once
#include <FMod/fmod.hpp>
#include <FMod/fmod_errors.h>

#include <Maths/Vector3.h>

#include <string>
#include <unordered_map>


const int MAX_CHANNELS = 512;

struct AudioSound
{
	FMOD::Sound* FModSound{ nullptr };
};


class AudioManager
{
public:
	bool Initialize();
	void Quit();
	void Update();
	void UpdateListener(const Vector3 listenerPos, const Vector3 listenerUp, const Vector3 listenerForward);

	void PauseAll(); //  for engine pause
	void ResumeAll();


	// ---------------------------------
	//  Load Sound
	// ---------------------------------
	AudioSound LoadSound(std::string soundFile);


	// ---------------------------------
	//  Audio Source part
	// ---------------------------------
	std::uint32_t CreateAudioSourceGroup(const std::string name = "");
	void ReleaseAudioSourceGroup(const std::uint32_t index);

	void PlaySoundOnAudioSource(const std::uint32_t index, const AudioSound& sound);
	void StopAudioSource(const std::uint32_t index);

	void PauseAudioSource(const std::uint32_t index, const bool pause);
	bool GetAudioSourcePaused(const std::uint32_t index);

	// volume (set and get) (check what is max volume for fmod)

	void SetAudioSourceGroupPos(const std::uint32_t index, const Vector3 position);
	Vector3 GetAudioSourceGroupPos(const std::uint32_t index);


	// ---------------------------------
	//  Instant Play Sound
	// ---------------------------------
	void InstantPlaySound2D(const AudioSound& sound);
	void InstantPlaySound3D(const AudioSound& sound, const Vector3 playPosition);

	void TestPlaySound(std::string soundFile);

private:
	FMOD::System* system{ nullptr };

	std::unordered_map<std::uint32_t, FMOD::ChannelGroup*> audioSourcesGroups;
	std::uint32_t audioSourcesGroupsID{ 0 };
};

