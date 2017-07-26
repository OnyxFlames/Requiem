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
	void update_string(const char c);
	void update();
	~Console();
	void draw();
	bool is_active();
	void toggle();
	void execute();
};

