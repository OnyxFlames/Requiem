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
	DialogBox()
	{
		mfont.loadFromFile("../resources/fonts/consola.ttf");
		mtext.setFont(mfont);
		
	}
	~DialogBox();

	bool isActive() { return misActive; }
	void isActive(bool active) { misActive = active; }

	void addText(const std::string &_text) { mtexts.push_back(_text); }
	void update() 
	{
		if (mtexts.size() > index)
			index++;
		else
			mtext.setString("Dialog box is out! :("); mtext.setScale(10.f, 10.f);

		update_dialogBox = true;
	}
	void setBounds(sf::FloatRect _bounds) { mbox = _bounds; }

	sf::Sprite& get_dialog()
	{

		//Temp: Assume the player sprite is 16x16
		const unsigned player_width = 16;

		if (!update_dialogBox)
			return dialogBox;
		else
			;//Do This v

		sf::RenderTexture ret;
		if (!ret.create(1280u, (720u / 2u) - player_width))
		{
			std::cerr << "Failed to create space to render dialog box!\n";
		}
		//TODO: Add texture for dialog box. Might look better.
		sf::RectangleShape shape;

		ret.clear();

		shape.setSize({ mbox.width, mbox.height - player_width });
		shape.setPosition({ mbox.left, mbox.top });
		shape.setPosition({ 0, 0 });
		shape.setFillColor(sf::Color(88, 88, 88));
		//shape.setOutlineColor(sf::Color::Red);
		ret.draw(shape);
		mtext.setPosition(mbox.left, mbox.top + player_width);
		ret.draw(mtext);
		ret.display();
		mbox_rendered = ret.getTexture();
		if (ret.getTexture().getSize().x == 0 || ret.getTexture().getSize().y == 0)
			std::cout << "Internal error: Failed to create buffer for dialogbox";
		dialogBox.setPosition(mbox.left, mbox.top);
		dialogBox.setTexture(mbox_rendered);
		//std::cout << "Drawing sprite at <" << dialogBox.getPosition().x << "," << dialogBox.getPosition().y << ">\nSize " << dialogBox.getGlobalBounds().width << "x" << dialogBox.getGlobalBounds().height << "\n";
		return dialogBox;
	}

};

