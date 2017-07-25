#include "Console.hpp"

#include <iostream>

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
		sf::RenderWindow &win = app->get_window();
		win.draw(text_box);
		win.draw(active_text);
		for (auto &h : history)
			win.draw(h);
	}
}

Console::~Console()
{
}

void Console::execute()
{
	if (command_str == "")
		return;
	sf::String str = active_text.getString();
	str.erase(str.getSize() - 1);
	active_text.setString(str);
	sf::Text temp = active_text;
	//temp.setPosition(1.f, 0.f);
	history.push_back(temp);

	for (size_t txt = history.size(); txt > 0; txt--)
	{
		history[history.size() - txt].setPosition(1.f, app->get_window_size().y - text_box.getGlobalBounds().height * (txt + 1));
	}

	command_str = "";
}
