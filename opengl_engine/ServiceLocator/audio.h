#pragma once
#include <Audio/audioUtils.h>
#include <string>
#include <Maths/Vector3.h>

class AudioSound;


/**
* The Audio Service class (the virtual class provided by the Locator).
*/
class Audio
{
public:
	virtual ~Audio() {}


// -----------------------------------------------------------------------------
//                 Load Sound
// -----------------------------------------------------------------------------

	/**
	* Load a sound in memory from file.
	* @param	soundFile	The path to the sound file to read.
	* @param	settings	(optionnal) Additionnal load settings for the sound.
	* @return				The newly created AudioSound object.
	*/
	virtual AudioSound LoadSound(std::string soundFile, SoundSettings settings = 0) = 0;



// -----------------------------------------------------------------------------
//                 Global Volume
// -----------------------------------------------------------------------------

	/**
	* Set the master volume.
	* @param	volume	The volume value to set. Between 0 and 1.
	*/
	virtual void SetGlobalVolume(const float volume) = 0;

	/**
	* Get the master volume value.
	* @return			The volume value.
	*/
	virtual float GetGlobalVolume() = 0;



// -----------------------------------------------------------------------------
//                 Audio Source
// -----------------------------------------------------------------------------

	/**
	* Create a ChannelGroup for an Audio Source component.
	* @param	spatialization	Is the channel made for 2D or 3D.
	* @param	name			(optionnal) The name to give to the ChannelGroup.
	* @return					The index of the created ChannelGroup.
	*/
	virtual std::uint32_t CreateAudioSourceGroup(ChannelSpatialization spatialization, const std::string name = "") = 0;

	/**
	* Release a ChannelGroup for an Audio Source Component destruction.
	* @param	index		The index of the ChannelGroup of the Audio Source component.
	*/
	virtual void ReleaseAudioSourceGroup(const std::uint32_t index) = 0;


	/**
	* Play a sound on an Audio Source component.
	* @param	index		The index of the ChannelGroup of the Audio Source component.
	* @param	sound		The sound to play. It must've been loaded with the same spatialization than the Audio Source ChannelGroup.
	* @param	loop		The number of time the sound will loop. -1 = infinite loop. 0 = play only once (defaut). The sound must've been loaded with the loop settings.
	*/
	virtual void PlaySoundOnAudioSource(const std::uint32_t index, const AudioSound& sound, const int loop = 0) = 0;

	/**
	* Stop every sound playing on an Audio Source component.
	* @param	index		The index of the ChannelGroup of the Audio Source component.
	*/
	virtual void StopAudioSource(const std::uint32_t index) = 0;
	

	/**
	* Set the pause value of an Audio Source component.
	* @param	index		The index of the ChannelGroup of the Audio Source component.
	* @param	pause		The pause value to set.
	*/
	virtual void PauseAudioSource(const std::uint32_t index, const bool pause) = 0;

	/**
	* Get the pause value of an Audio Source component.
	* @param	index		The index of the ChannelGroup of the Audio Source component.
	* @return				The pause value of the Audio Source component.
	*/
	virtual bool GetAudioSourcePaused(const std::uint32_t index) = 0;
	

	/**
	* Set the volume of an Audio Source component.
	* @param	index		The index of the ChannelGroup of the Audio Source component.
	* @param	volume		The volume value to set. Between 0 and 1.
	*/
	virtual void SetAudioSourceGroupVolume(const std::uint32_t index, const float volume) = 0;

	/**
	* Get the volume value of an Audio Source component.
	* @param	index		The index of the ChannelGroup of the Audio Source component.
	* @return				The volume value of the Audio Source component.
	*/
	virtual float GetAudioSourceGroupVolume(const std::uint32_t index) = 0;
	

	/**
	* Set the position in world space of an Audio Source component. It must've been loaded with a 3D ChannelGroup.
	* @param	index		The index of the ChannelGroup of the Audio Source component.
	* @param	poition		The position value to set. Between 0 and 1.
	*/
	virtual void SetAudioSourceGroupPos(const std::uint32_t index, const Vector3 position) = 0;

	/**
	* Get the position in world space of an Audio Source component. It must've been loaded with a 3D ChannelGroup.
	* @param	index		The index of the ChannelGroup of the Audio Source component.
	* @return				The position in world space of the Audio Source component.
	*/
	virtual Vector3 GetAudioSourceGroupPos(const std::uint32_t index) = 0;



// -----------------------------------------------------------------------------
//                 Instant Play Sound
// -----------------------------------------------------------------------------

	/**
	* Play a 2D sound without an Audio Source component.
	* @param	sound		The sound to play. It must've been loaded at a 2D sound.
	* @param	volume		The volume value to play the sound with. Between 0 and 1.
	* @param	loop		The number of time the sound will loop. -1 = infinite loop. 0 = play only once (defaut). The sound must've been loaded with the loop settings.
	*/
	virtual void InstantPlaySound2D(const AudioSound& sound, const float volume = 1.0f, const int loop = 0) = 0;

	/**
	* Play a 3D sound without an Audio Source component.
	* @param	sound			The sound to play. It must've been loaded at a 3D sound.
	* @param	playPosition	The position in world space the sound will be located.
	* @param	volume			The volume value to play the sound with. Between 0 and 1.
	* @param	loop			The number of time the sound will loop. -1 = infinite loop. 0 = play only once (defaut). The sound must've been loaded with the loop settings.
	*/
	virtual void InstantPlaySound3D(const AudioSound& sound, const Vector3 playPosition, const float volume = 1.0f, const int loop = 0) = 0;
};