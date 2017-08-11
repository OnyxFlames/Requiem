#pragma once

#include "Triggers/TriggerBase.hpp"

#include <SFML/Audio.hpp>

class SoundTrigger : TriggerBase
{
private:
	bool triggered = false;
	sf::FloatRect trigger;
	sf::SoundBuffer soundbuff;
	sf::Sound sound;
public:
	SoundTrigger();
	virtual bool test(sf::FloatRect &_test) override;
	bool load_sound(const std::string &path);
	~SoundTrigger();
};

