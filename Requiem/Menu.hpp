#pragma once

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#include "ResourceManagers/TextureManager.hpp"

class Menu
{
private:
	sf::Font menu_font;
	// text_identifier - actual item
	// lets try this method over storing in an array
	std::map<std::string, sf::Text> text;
	std::vector<sf::Sprite> ui_element;
	std::unique_ptr<TextureManager> tm;
public:
	Menu();
	~Menu();
};

