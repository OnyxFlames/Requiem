#include "Console.hpp"

#include <iostream>
#include <cctype>

void to_lower(std::string& str)
{
	for (auto &c : str)
		c = std::tolower(c);
}

Console::Console()
{
}

Console::Console(Application &_app, sf::Font &_font)
{
	app = &_app;
	unsigned width = app->get_window_size().x, height = app->get_window_size().y;
	text_box.setSize({ width / 2.f, 25.f });
	text_box.setPosition({1.f, height - text_box.getGlobalBounds().height});
	text_box.setFillColor(sf::Color(127, 127, 127, 82));
	// This is needed or the program will crash
	font = &_font;
	//...
	font->loadFromFile("../resources/fonts/consola.ttf");
	active_text.setFont(*font);
	active_text.setFillColor(sf::Color::White);
	active_text.setPosition(1.f, height - text_box.getGlobalBounds().height);
	active_text.setString("");
	active_text.setCharacterSize(20);
}

void Console::draw()
{
	if (active)
	{
		sf::RenderWindow &win = app->window;
		win.draw(text_box);
		win.draw(active_text);
		for (auto &h : history)
			win.draw(h);
	}
}

void Console::update_string(const char c)
{
	if (c != '\b')
		command_str += c;
	else if (command_str.size() > 0)
		command_str.erase(command_str.begin() + command_str.size() - 1);
	if (command_str[0] == 13)
		command_str.erase(command_str.begin());
	active_text.setString(command_str + '|');
}
void Console::update()
{
	sf::String str = active_text.getString();
	str.erase(str.getSize() - 1);
	active_text.setString(str);
	sf::Text temp = active_text;
	history.push_back(temp);
	command_str = "";
	for (size_t txt = history.size(); txt > 0; txt--)
	{
		history[history.size() - txt].setPosition(1.f, app->get_window_size().y - text_box.getGlobalBounds().height * (txt + 1));
	}
}
bool Console::is_active()
{
	return active;
}
void Console::toggle()
{
	active = !active;
}

Console::~Console()
{
}

void Console::execute()
{
	if (command_str == "")
		return;
	std::string command = command_str.substr(0, command_str.find(' '));
	std::string arg = command_str.substr(command.size()+1);
	if (arg.size() == 0)
		return;
	to_lower(arg);
	if (command == "/voidcolor" || command == "/voidcolour")
	{
		if (arg == "black")
			app->void_color = sf::Color::Black;
		else if (arg == "red")
			app->void_color = sf::Color::Red;
		else if (arg == "green")
			app->void_color = sf::Color::Green;
		else if (arg == "blue")
			app->void_color = sf::Color::Blue;
		else if (arg == "grey" || arg == "gray")
			app->void_color = sf::Color(127, 127, 127);
		else if (arg == "white")
			app->void_color = sf::Color(255, 255, 255);
		else
			active_text.setString("Error: '" + arg + "' is not a valid option.");
	}
	update();
}
