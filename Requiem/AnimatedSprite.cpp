#include "AnimatedSprite.hpp"



AnimatedSprite::AnimatedSprite()
{
}

void AnimatedSprite::update(sf::Time dt)
{
	//TODO: Add check to see if value is -1 at any time, if it is, replace that specific value with the previous steps value (making changes relative rather than absolute)
	if (time_step >= MAX_TIME)
	{
		time_step = sf::seconds(0);
	}
	else
	{
		time_step += dt;
	}
	for (unsigned char i = 0; i < iterations.size(); i++)
	{
		if (time_step >= iterations[i])
		{
			setTextureRect(sf::IntRect(text_rects[i].first.x, text_rects[i].first.y, text_rects[i].second.x, text_rects[i].second.y));
		}
	}
}

void AnimatedSprite::load_from_file(const std::string &filename)
{
	std::ifstream anim(filename);
	std::ifstream animmax(filename + "max");
	std::ifstream animstep(filename + "step");
	if (!anim.is_open() || !animmax.is_open() || !animstep.is_open())
		std::cerr << "Error loading animation data for \'" << filename << "\'\n";

	std::string buff = "";
	animmax >> buff;
	MAX_TIME = sf::milliseconds(std::stoi(buff));
	
	while (animstep >> buff)
	{
		iterations.push_back(sf::milliseconds(std::stoi(buff)));
	}

	for (unsigned short i = 0; i < iterations.size(); i++)
	{
		int x, y, width, height;

		anim >> buff;
		x = std::stoi(buff);
		
		anim >> buff;
		y = std::stoi(buff);
		
		anim >> buff;
		width = std::stoi(buff);
		
		anim >> buff;
		height = std::stoi(buff);
		
		text_rects.push_back(std::make_pair<sf::Vector2i, sf::Vector2i>(sf::Vector2i(x, y), sf::Vector2i(width, height)));
	}
}

AnimatedSprite::~AnimatedSprite()
{
}
// Example code that breaks down the current update() function, TODO: remove later
void AnimatedSprite::update_old(sf::Time dt)
{
	if (time_step >= MAX_TIME)
	{
		time_step = sf::seconds(0);
	}
	else
	{
		time_step += dt;
	}
	// Below second step, means it's still on it's first step.
	if (time_step < sf::seconds(1))
	{
		setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
	// Second step, after one second has passed.
	if (time_step >= sf::seconds(1))
	{
		setTextureRect(sf::IntRect(0, 17, 16, 16));
	}
	// Third step, 2 seconds
	if (time_step >= sf::seconds(2))
	{
		setTextureRect(sf::IntRect(0, 34, 16, 16));
	}
	// Fourth step, 3 seconds
	if (time_step >= sf::seconds(3))
	{
		setTextureRect(sf::IntRect(0, 51, 16, 16));
	}
	// After this, the sprite should hit the max value(defined in the *.animmax file)
}
