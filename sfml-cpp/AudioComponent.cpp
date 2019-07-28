#include "AudioComponent.h"
#include <string>

void AudioComponent::LoadClip(std::string path)
{
	if (!buffer.loadFromFile(path))
	{
		std::cout << "AudioComponent::LoadClip - Failed to load " << path << std::endl;
	}

	sound.setBuffer(buffer);

}

void AudioComponent::Play()
{
	sound.play();
}

void AudioComponent::Stop()
{
	sound.stop();
}

bool AudioComponent::IsPlaying()
{
	return sound.getStatus() == sf::SoundSource::Playing;
}
