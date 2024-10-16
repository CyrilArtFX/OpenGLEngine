#include "audioSourceComponent.h"
#include <ServiceLocator/locator.h>


//  Constructors
AudioSourceComponent::AudioSourceComponent() : associatedObject(nullptr), sourceSpatialization(ChannelSpatialization::Channel2D), audioManagerRef(Locator::getAudio())
{
	channelIndex = std::numeric_limits<std::uint32_t>::max();
	//  max channel index will never be created by the audio manager, it prevent a badly created audio source component to be able to play a sound
}

AudioSourceComponent::AudioSourceComponent(Object* objectToAssociate, ChannelSpatialization spatialization, std::string name) : associatedObject(objectToAssociate), sourceSpatialization(spatialization), audioManagerRef(Locator::getAudio())
{
	channelIndex = audioManagerRef.CreateAudioSourceGroup(spatialization, name);

	if (sourceSpatialization == ChannelSpatialization::Channel3D)
	{
		associatedObject->onTransformUpdated.registerObserver(this, Bind_0(&AudioSourceComponent::onAssociatedObjectMoved));
	}
}

AudioSourceComponent::AudioSourceComponent(const AudioSourceComponent& other) : associatedObject(other.associatedObject), sourceSpatialization(other.sourceSpatialization), channelIndex(other.channelIndex), audioManagerRef(Locator::getAudio())
{
	if (sourceSpatialization == ChannelSpatialization::Channel3D)
	{
		associatedObject->onTransformUpdated.registerObserver(this, Bind_0(&AudioSourceComponent::onAssociatedObjectMoved));
	}
}

/*AudioSourceComponent& AudioSourceComponent::operator=(const AudioSourceComponent& other)
{
	associatedObject = other.associatedObject;
	sourceSpatialization = other.sourceSpatialization;
	channelIndex = other.channelIndex;

	if (sourceSpatialization == ChannelSpatialization::Channel3D)
	{
		associatedObject->onTransformUpdated.registerObserver(this, Bind_0(&AudioSourceComponent::onAssociatedObjectMoved));
	}

	return *this;
}*/


//  Release
void AudioSourceComponent::releaseChannel()
{
	associatedObject->onTransformUpdated.unregisterObserver(this);
	audioManagerRef.ReleaseAudioSourceGroup(channelIndex);
}


//  Play and Stop
void AudioSourceComponent::playSound(const AudioSound& sound, const int loop)
{
	audioManagerRef.PlaySoundOnAudioSource(channelIndex, sound, loop);
}

void AudioSourceComponent::stopSound() const
{
	audioManagerRef.StopAudioSource(channelIndex);
}


//  Pause
void AudioSourceComponent::setPause(const bool pause)
{
	audioManagerRef.PauseAudioSource(channelIndex, pause);
}

bool AudioSourceComponent::getPaused() const
{
	return audioManagerRef.GetAudioSourcePaused(channelIndex);
}


//  Volume
void AudioSourceComponent::setVolume(const float volume)
{
	audioManagerRef.SetAudioSourceGroupVolume(channelIndex, volume);
}

float AudioSourceComponent::getVolume() const
{
	return audioManagerRef.GetAudioSourceGroupVolume(channelIndex);
}


//  Offset
void AudioSourceComponent::setOffset(const Vector3 offset)
{
	if (sourceSpatialization != ChannelSpatialization::Channel3D) return;

	objectOffset = offset;
	onAssociatedObjectMoved();
}

Vector3 AudioSourceComponent::getOffset() const
{
	if (sourceSpatialization != ChannelSpatialization::Channel3D) return Vector3::zero;

	return objectOffset;
}


//  Auto-update pos
void AudioSourceComponent::onAssociatedObjectMoved()
{
	if (sourceSpatialization != ChannelSpatialization::Channel3D) return;

	audioManagerRef.SetAudioSourceGroupPos(channelIndex, associatedObject->getPosition() + objectOffset);
}

