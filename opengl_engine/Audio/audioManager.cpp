#include "audioManager.h"
#include <iostream>


// --------------------------------------------------------------
//            Core part
// --------------------------------------------------------------

//  Initialize and Quit
bool AudioManager::Initialize()
{
	FMOD_RESULT result;

	//  intialize fmod debug
	result = FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR, FMOD_DEBUG_MODE_TTY);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Init Error: Failed to initialize FMOD debug: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	//  create fmod core system object
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Init Error: Failed to create FMOD core system: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	//  initialize fmod core system
	result = system->init(MAX_CHANNELS, FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Init Error: Failed to initialize FMOD core system: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	//  setup basic 3D settings
	result = system->set3DSettings(1.0f, 1.0f, 1.0f);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Init Error: Failed to setup FMOD 3D settings: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	return true;
}

void AudioManager::Quit()
{
	if (!system) return;
	
	system->release();
}


//  Updates
void AudioManager::Update()
{
	if (!system) return;

	system->update();
}

void AudioManager::UpdateListener(const Vector3 listenerPos, const Vector3 listenerUp, const Vector3 listenerForward)
{
	if (!system) return;

	const FMOD_VECTOR listener_pos = listenerPos.toFMOD();
	const FMOD_VECTOR listener_vel = Vector3::zero.toFMOD();
	const FMOD_VECTOR listener_forward = (-listenerForward).toFMOD(); //  need to reverse forward otherwise the sound come from the wrong ear (don't know why)
	const FMOD_VECTOR listener_up = listenerUp.toFMOD();

	FMOD_RESULT result;
	result = system->set3DListenerAttributes(0, &listener_pos, &listener_vel, &listener_forward, &listener_up);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD Update Listener Error: " << FMOD_ErrorString(result) << "\n";
	}
}



// --------------------------------------------------------------
//            Engine pause part
// --------------------------------------------------------------

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



// --------------------------------------------------------------
//            Load Sound part
// --------------------------------------------------------------

AudioSound AudioManager::LoadSound(std::string soundFile, SoundSettings settings)
{
	FMOD_MODE spatialization_mode = FMOD_2D;
	if (settings & ACTIVATE_3D)
		spatialization_mode = FMOD_3D;

	FMOD_MODE load_mode = FMOD_CREATESAMPLE;
	if (settings & ACTIVATE_STREAM)
		load_mode = FMOD_CREATESTREAM;

	FMOD_MODE loop_mode = FMOD_LOOP_OFF;
	if (settings & ACTIVATE_LOOP)
		loop_mode = FMOD_LOOP_NORMAL;


	FMOD::Sound* sound;
	FMOD_RESULT result;
	result = system->createSound(soundFile.c_str(), spatialization_mode | load_mode | loop_mode | FMOD_3D_LINEARSQUAREROLLOFF, 0, &sound);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to load a sound from file. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
	}

	return AudioSound(sound, settings);
}



// --------------------------------------------------------------
//            Audio Source part
// --------------------------------------------------------------

//  Create and Release
std::uint32_t AudioManager::CreateAudioSourceGroup(ChannelSpatialization spatialization, const std::string name)
{
	if (!system) return 0;

	FMOD_RESULT result;

	audioSourcesGroups.emplace(audioSourcesGroupsID, nullptr);
	result = system->createChannelGroup(name.c_str(), &audioSourcesGroups[audioSourcesGroupsID]);
	FMOD::ChannelGroup* group_create = audioSourcesGroups[audioSourcesGroupsID];
	audioSourcesGroupsID++;

	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to create a new audio source group. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
		return audioSourcesGroupsID - 1;
	}

	if (spatialization == ChannelSpatialization::Channel3D)
	{
		group_create->setMode(FMOD_3D);
	}

	return audioSourcesGroupsID - 1;
}

void AudioManager::ReleaseAudioSourceGroup(const std::uint32_t index)
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


//  Play and Stop
void AudioManager::PlaySoundOnAudioSource(const std::uint32_t index, const AudioSound& sound, const int loop)
{
	if (!system) return;

	if (!sound.isValid())
	{
		std::cout << "Audio Manager Error: Tried to play a sound on an audio source group with an unitialized sound.\n";
		return;
	}

	FMOD::ChannelGroup* group_sound = audioSourcesGroups[index];
	if (group_sound == nullptr)
	{
		std::cout << "Audio Manager Error: Tried to play a sound on an audio source group with a non-registered index." << "\n";
		return;
	}

	if (sound.hasSetting(ACTIVATE_3D) != (GetGroupSpatialization(group_sound) == ChannelSpatialization::Channel3D))
	{
		std::cout << "Audio Manager Error: Tried to play a sound on an audio source that hasn't the same spatialization." << "\n";
		return;
	}


	group_sound->stop();

	FMOD::Channel* channel;
	FMOD_RESULT result;
	result = system->playSound(sound.getFMod(), group_sound, false, &channel);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to play a sound on an audio source group. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
		return;
	}


	if (loop != 0 && !sound.hasSetting(ACTIVATE_LOOP))
	{
		std::cout << "Audio Manager Error: Tried to play a sound on an audio source group with loop on an sound that hasn't loop activated.\n";
	}
	else
	{
		result = channel->setLoopCount(loop);
		if (result != FMOD_OK)
		{
			std::cout << "Audio Manager Error: Failed to set loop count on an sound played on an audio source group. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
			//  don't return if setting loop failed, the sound has already started playing so we need to setup the position of the channel
		}
	}

	if (sound.hasSetting(ACTIVATE_3D))
	{
		FMOD_VECTOR pos;
		FMOD_VECTOR vel;
		group_sound->get3DAttributes(&pos, &vel);
		channel->set3DAttributes(&pos, &vel);
	}

	group_sound->setPaused(false);
}

void AudioManager::StopAudioSource(const std::uint32_t index)
{
	FMOD::ChannelGroup* group_stop = audioSourcesGroups[index];
	if (group_stop == nullptr)
	{
		std::cout << "Audio Manager Error: Tried to stop an audio source group with a non-registered index." << "\n";
		return;
	}

	group_stop->stop();
}


//  Pause (set and get)
void AudioManager::PauseAudioSource(const std::uint32_t index, const bool pause)
{
	FMOD::ChannelGroup* group_pause = audioSourcesGroups[index];
	if (group_pause == nullptr)
	{
		std::cout << "Audio Manager Error: Tried to pause an audio source group with a non-registered index." << "\n";
		return;
	}

	group_pause->setPaused(pause);
}

bool AudioManager::GetAudioSourcePaused(const std::uint32_t index)
{
	FMOD::ChannelGroup* group_pause = audioSourcesGroups[index];
	if (group_pause == nullptr)
	{
		std::cout << "Audio Manager Error: Tried to get an audio source group paused with a non-registered index." << "\n";
		return false;
	}

	bool paused = false;

	FMOD_RESULT result;
	result = group_pause->getPaused(&paused);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to get an audio source group paused. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
		return false;
	}

	return paused;
}


//  Volume (set and get)
void AudioManager::SetAudioSourceGroupVolume(const std::uint32_t index, const float volume)
{
	FMOD::ChannelGroup* group_volume = audioSourcesGroups[index];
	if (group_volume == nullptr)
	{
		std::cout << "Audio Manager Error: Tried to set an audio source group volume with a non-registered index." << "\n";
		return;
	}

	FMOD_RESULT result;
	result = group_volume->setVolume(volume);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to set an audio source group volume. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
	}
}

float AudioManager::GetAudioSourceGroupVolume(const std::uint32_t index)
{
	FMOD::ChannelGroup* group_volume = audioSourcesGroups[index];
	if (group_volume == nullptr)
	{
		std::cout << "Audio Manager Error: Tried to get an audio source group volume with a non-registered index." << "\n";
		return 0.0f;
	}

	float volume;
	FMOD_RESULT result;
	result = group_volume->getVolume(&volume);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to get an audio source group volume. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
		return 0.0f;
	}

	return volume;
}


//  Position (set and get)
void AudioManager::SetAudioSourceGroupPos(const std::uint32_t index, const Vector3 position)
{
	FMOD::ChannelGroup* group_pos = audioSourcesGroups[index];
	if (group_pos == nullptr)
	{
		std::cout << "Audio Manager Error: Tried to set an audio source group position with a non-registered index." << "\n";
		return;
	}

	const FMOD_VECTOR pos = position.toFMOD();
	const FMOD_VECTOR vel = Vector3::zero.toFMOD();

	FMOD_RESULT result;
	result = group_pos->set3DAttributes(&pos, &vel);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to set an audio source group position. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
	}
}

Vector3 AudioManager::GetAudioSourceGroupPos(const std::uint32_t index)
{
	FMOD::ChannelGroup* group_pos = audioSourcesGroups[index];
	if (group_pos == nullptr)
	{
		std::cout << "Audio Manager Error: Tried to get an audio source group position with a non-registered index." << "\n";
		return Vector3::zero;
	}

	FMOD_VECTOR pos;
	FMOD_VECTOR vel;

	FMOD_RESULT result;
	result = group_pos->get3DAttributes(&pos, &vel);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to get an audio source group position. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
		return Vector3::zero;
	}

	return Vector3::FromFMOD(pos);
}



// --------------------------------------------------------------
//            Instant Play Sound part
// --------------------------------------------------------------

void AudioManager::InstantPlaySound2D(const AudioSound& sound, const float volume, const int loop)
{
	if (!system) return;

	if (!sound.isValid())
	{
		std::cout << "Audio Manager Error: Tried to instantly play a 2D sound with an unitialized sound.\n";
		return;
	}

	if (sound.hasSetting(ACTIVATE_3D))
	{
		std::cout << "Audio Manager Error: Tried to instantly play a 2D sound with a 3D sound.\n";
		return;
	}

	FMOD::Channel* channel;
	FMOD_RESULT result;
	result = system->playSound(sound.getFMod(), 0, false, &channel);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to instantly play a 2D sound. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
		return;
	}

	if (loop != 0 && !sound.hasSetting(ACTIVATE_LOOP))
	{
		std::cout << "Audio Manager Error: Tried to instantly play a 2D sound with loop on an sound that hasn't loop activated.\n";
	}
	else
	{
		result = channel->setLoopCount(loop);
		if (result != FMOD_OK)
		{
			std::cout << "Audio Manager Error: Failed to set loop count on an instantly played 2D sound. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
			//  don't return if setting loop failed, the sound has already started playing so we need to setup the volume of the channel
		}
	}

	result = channel->setVolume(volume);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to set volume on an instantly played 2D sound. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
	}
}

void AudioManager::InstantPlaySound3D(const AudioSound& sound, const Vector3 playPosition, const float volume, const int loop)
{
	if (!system) return;

	if (!sound.isValid())
	{
		std::cout << "Audio Manager Error: Tried to instantly play a 3D sound with an unitialized sound.\n";
		return;
	}

	if (!sound.hasSetting(ACTIVATE_3D))
	{
		std::cout << "Audio Manager Error: Tried to instantly play a 3D sound with a 2D sound.\n";
		return;
	}

	FMOD::Channel* channel;
	FMOD_RESULT result;
	result = system->playSound(sound.getFMod(), 0, false, &channel);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to instantly play a 3D sound. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
		return;
	}

	if (loop != 0 && !sound.hasSetting(ACTIVATE_LOOP))
	{
		std::cout << "Audio Manager Error: Tried to instantly play a 3D sound with loop on an sound that hasn't loop activated.\n";
	}
	else
	{
		result = channel->setLoopCount(loop);
		if (result != FMOD_OK)
		{
			std::cout << "Audio Manager Error: Failed to set loop count on an instantly played 3D sound. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
			//  don't return if setting loop failed, the sound has already started playing so we need to setup the position and volume of the channel
		}
	}

	result = channel->setVolume(volume);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to set volume on an instantly played 3D sound. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
		//  don't return if setting volume failed, the sound has already started playing so we need to setup the position of the channel
	}

	FMOD_VECTOR sound_pos = playPosition.toFMOD();
	FMOD_VECTOR sound_vel = Vector3::zero.toFMOD();
	result = channel->set3DAttributes(&sound_pos, &sound_vel);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to set position on an instantly played 3D sound. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
	}
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



// --------------------------------------------------------------
//            Helping Functions part
// --------------------------------------------------------------

ChannelSpatialization AudioManager::GetGroupSpatialization(FMOD::ChannelGroup* group)
{
	FMOD_RESULT result;
	FMOD_MODE mode;

	result = group->getMode(&mode);
	if (result != FMOD_OK)
	{
		std::cout << "Audio Manager Error: Failed to get the mode of a channel group. | Associated FMOD Error: " << FMOD_ErrorString(result) << "\n";
		return ChannelSpatialization::Channel2D;
	}

	if (mode & FMOD_2D)
	{
		return ChannelSpatialization::Channel2D;
	}

	if (mode & FMOD_3D)
	{
		return ChannelSpatialization::Channel3D;
	}
}
