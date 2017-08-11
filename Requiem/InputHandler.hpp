#pragma once

#include "Application.hpp"



#include <SFML/Graphics.hpp>

enum InputMode {
	unknown,
	menu,
	console,
	game,
};

class Application;

class InputHandler
{
private:
	Application *app;
	InputMode mode = game;

	void handle_menu_input(sf::Event &e);
	void handle_console_input(sf::Event &e);
	void handle_game_input(sf::Event &e);
public:
	InputHandler(Application &_app);
	~InputHandler();
	void handle(sf::Event &e);
	InputMode getMode();
};

