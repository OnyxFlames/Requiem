#include "SoundTrigger.hpp"

#include <iostream>

SoundTrigger::SoundTrigger()
{
}

bool SoundTrigger::test(sf::FloatRect &_test)
{
	if (_test.intersects(trigger) && !triggered)
	{
		std::cout << "Sound triggered.\n";
		sound.play();
		triggered = true;
	}
	else
		triggered = false;
}

bool SoundTrigger::load_sound(const std::string &path)
{
	soundbuff.loadFromFile(path);
	sound.setBuffer(soundbuff);
}

SoundTrigger::~SoundTrigger()
{
}
