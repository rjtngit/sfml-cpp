#pragma once
#include "GameComponent.h"
#include <string>
#include <SFML/Audio.hpp>

class AudioComponent : public GameComponent
{
public:
	void LoadClip(std::string path);
	void Play();
	void Stop();
	bool IsPlaying();

private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
};