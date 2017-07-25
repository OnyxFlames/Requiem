#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "../Application.hpp"

class Application;

class Console
{
private:
	Application* app;

	sf::Font* font = &sf::Font();
	sf::Text active_text;
	std::vector<sf::Text> history;
	sf::RectangleShape text_box;
	std::string command_str;
	bool active = false;
public:
	Console();
	Console(Application &_app, sf::Font &_font);
	void update_string(const char c)
	{
		if (c != '\b')
			command_str += c;
		else if (command_str.size() > 0)
			command_str.erase(command_str.begin() + command_str.size() - 1);
		if (command_str[0] == 13)
			command_str.erase(command_str.begin());
		active_text.setString(command_str + '|');
	}
	void update()
	{

	}
	~Console();
	void draw();
	bool is_active()
	{
		return active;
	}
	void toggle()
	{
		active = !active;
	}
	void execute();
};

