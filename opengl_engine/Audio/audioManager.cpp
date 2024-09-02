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

	//  create fmod core system object
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD Init Error: Failed to create FMOD core system: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	//  initialize fmod core system
	result = system->init(MAX_CHANNELS, FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD Init Error: Failed to initialize FMOD core system: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	//  setup basic 3D settings
	result = system->set3DSettings(1.0f, 1.0f, 1.0f);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD Init Error: Failed to setup FMOD 3D settings: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	return true;
}

void AudioManager::Quit()
{
	if (!system) return;
	
	system->release();
}

void AudioManager::Update()
{
	if (!system) return;

	system->update();
}

void AudioManager::UpdateListener(const Vector3 listenerPos, const Vector3 listenerUp, const Vector3 listenerForward)
{
	if (!system) return;

	FMOD_VECTOR listener_pos = listenerPos.toFMOD();
	FMOD_VECTOR listener_vel = Vector3::zero.toFMOD();
	FMOD_VECTOR listener_forward = (-listenerForward).toFMOD(); //  need to reverse forward otherwise the sound come from the wrong ear (don't know why)
	FMOD_VECTOR listener_up = listenerUp.toFMOD();

	FMOD_RESULT result;
	result = system->set3DListenerAttributes(0, &listener_pos, &listener_vel, &listener_forward, &listener_up);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD Update Listener Error: " << FMOD_ErrorString(result) << "\n";
	}
}

void AudioManager::PauseAll()
{
	if (!system) return;

	FMOD::ChannelGroup* master;
	system->getMasterChannelGroup(&master);
	master->setPaused(true);
}

void AudioManager::ResumeAll()
{
	if (!system) return;

	FMOD::ChannelGroup* master;
	system->getMasterChannelGroup(&master);
	master->setPaused(false);
}

std::uint32_t AudioManager::CreateAudioSourceGroup(std::string name)
{
	if (!system) return;

	FMOD_RESULT result;

	audioSourcesGroups.emplace(audioSourcesGroupsID, nullptr);
	result = system->createChannelGroup(name.c_str(), &audioSourcesGroups[audioSourcesGroupsID]);
	audioSourcesGroupsID++;

	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to create a new audio source group. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
	}

	return audioSourcesGroupsID - 1;
}

void AudioManager::ReleaseAudioSourceGroup(std::uint32_t index)
{
	FMOD::ChannelGroup* group_release = audioSourcesGroups[index];
	if (group_release == nullptr)
	{
		std::cout << "Audio Manager Error: Tried to release an audio source group with a non-registered index." << "\n";
		return;
	}

	FMOD_RESULT result;
	result = group_release->release();
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to release an audio source group. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
		return;
	}

	audioSourcesGroups.erase(index);
}

void AudioManager::TestPlaySound(std::string soundFile)
{
	FMOD::Sound* sound;
	FMOD_RESULT result = system->createSound(soundFile.c_str(), FMOD_2D | FMOD_CREATESTREAM, 0, &sound);
	if (result != FMOD_OK)
	{
		std::cout << FMOD_ErrorString(result) << "\n";
	}
	sound->set3DMinMaxDistance(0.5f, 5000.0f);
	FMOD::Channel* channel;
	result = system->playSound(sound, 0, false, &channel);
	FMOD_VECTOR sound_pos = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR sound_vel = { 0.0f, 0.0f, 0.0f };
	channel->set3DAttributes(&sound_pos, &sound_vel);
	channel->setPaused(false);
}
