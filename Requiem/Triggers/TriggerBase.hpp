#pragma once

#include <SFML/Graphics.hpp>

class TriggerBase
{
private:
	bool triggered = false;
	sf::FloatRect trigger;
public:
	TriggerBase();
	virtual bool test(sf::FloatRect &_test) = 0;
	~TriggerBase();
};