#pragma once
#include <Objects/object.h>
#include <Audio/audioUtils.h>
#include <Events/observer.h>

class AudioSound;


/** Audio Source Component
*/
class AudioSourceComponent : public Observer
{
public:
	AudioSourceComponent();
	AudioSourceComponent(Object* objectToAssociate, ChannelSpatialization spatialization, std::string name = "");
	AudioSourceComponent(const AudioSourceComponent& other);
	AudioSourceComponent& operator=(const AudioSourceComponent& other) = delete;

	/**
	* Release the audio channel of this audio source component. Useful if you want to kill the object that has this component.
	*/
	void ReleaseChannel();

	std::uint32_t getChannelIndex() const { return channelIndex; }
	ChannelSpatialization getChannelSpatialization() const { return sourceSpatialization; }
	Object* getAssociatedObject() const { return associatedObject; }


	/**
	* Play a sound on this Audio Source component.
	* @param	sound		The sound to play. It must've been loaded with the same spatialization than this component.
	* @param	loop		The number of time the sound will loop. -1 = infinite loop. 0 = play only once (defaut). The sound must've been loaded with the loop settings.
	*/
	void playSound(const AudioSound& sound, const int loop = 0);

	/**
	* Stop every sound playing on this Audio Source component.
	*/
	void stopSound() const;


	/**
	* Set the pause value.
	* @param	pause		The pause value to set.
	*/
	void setPause(const bool pause);

	/**
	* Get the pause value.
	* @return		The pause value.
	*/
	bool getPaused() const;


	/**
	* Set the volume.
	* @param	volume		The volume value to set. Between 0 and 1.
	*/
	void setVolume(const float volume);

	/**
	* Get the volume value.
	* @return		The volume value.
	*/
	float getVolume() const;


	/**
	* Set the offset position from associated object. It must've been created with the 3D spatialization.
	* @param	poition		The offset value to set.
	*/
	void setOffset(const Vector3 offset);

	/**
	* Get the offset position from associated object. It must've been created with the 3D spatialization.
	* @return		The offset value.
	*/
	Vector3 getOffset() const;


private:
	void onAssociatedObjectMoved();

	std::uint32_t channelIndex;
	ChannelSpatialization sourceSpatialization;

	Object* associatedObject;
	Vector3 objectOffset{ Vector3::zero };

	class Audio& audioManagerRef;
};

