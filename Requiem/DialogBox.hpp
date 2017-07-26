#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Debug_Utils.hpp"

class DialogBox
{
private:
	bool misActive = false;

	// the box that the dialog is handled in
	sf::FloatRect mbox;

	sf::Text mtext;
	//TODO: Make dialogbox font load from ResourceManager<Font> when implemented
	sf::Font mfont;

	unsigned char index;
	std::vector<std::string> mtexts;

	sf::Texture mbox_rendered;
	sf::Sprite dialogBox;

	bool update_dialogBox = false;
public:
	DialogBox();
	~DialogBox();

	bool isActive();
	void isActive(bool active);

	void addText(const std::string &_text);
	void update();
	void setBounds(sf::FloatRect _bounds);

	sf::Sprite& get_dialog();

};

