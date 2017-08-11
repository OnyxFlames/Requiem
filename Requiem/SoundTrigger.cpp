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
		return triggered;
	}
	else
		triggered = false;
	return triggered;
}

bool SoundTrigger::load_sound(const std::string &path)
{
	
	if (soundbuff.loadFromFile(path))
	{
		sound.setBuffer(soundbuff);
		return true;
	}
	return false;
}

SoundTrigger::~SoundTrigger()
{
}
