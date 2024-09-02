#pragma once
#include <FMod/fmod.hpp>
#include <FMod/fmod_errors.h>

#include <Maths/Vector3.h>

#include <string>
#include <unordered_map>


const int MAX_CHANNELS = 512;


class AudioManager
{
public:
	bool Initialize();
	void Quit();
	void Update();
	void UpdateListener(const Vector3 listenerPos, const Vector3 listenerUp, const Vector3 listenerForward);

	void PauseAll(); //  for engine pause
	void ResumeAll();

	std::uint32_t CreateAudioSourceGroup(std::string name = "");
	void ReleaseAudioSourceGroup(std::uint32_t index);

	void TestPlaySound(std::string soundFile);

private:
	FMOD::System* system{ nullptr };

	std::unordered_map<std::uint32_t, FMOD::ChannelGroup*> audioSourcesGroups;
	std::uint32_t audioSourcesGroupsID{ 0 };
};

