#pragma once

#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>
#include <utility>

//TODO: Separate AnimatedSprite object and Animation so you can swap animations with the same sprite
//		(AnimatedSprite -> AnimatableSprite, which holds a list of animations and functions to swap through them)

class AnimatedSprite : public sf::Sprite
{
private:
	sf::Time MAX_TIME = sf::seconds(0);
	sf::Time time_step;
	std::vector<sf::Time> iterations;
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> text_rects;
public:
	AnimatedSprite();
	void update(sf::Time dt);
	void update_old(sf::Time dt);
	void load_from_file(const std::string &filename);
	~AnimatedSprite();
};

