#include "Application.hpp"

sf::RenderWindow& Application::get_window()
{
	return window;
}

void Application::render()
{

	static sf::Clock timer;
	static sf::Time frame_count;
	static unsigned int frames = 0;
	if (frame_count <= sf::milliseconds(1000))
	{
		frames++;
		frame_count += timer.restart();
	}
	else
	{
		frame_count = sf::seconds(0.f);
		texts.at(graphic_rate)->setString("Graphic rate: " + std::to_string(frames));
		frames = 0;
	}

	window.clear(void_color);

	for (auto &c : tilemaps)
		window.draw(*c);
	for (auto &c : sprites)
		window.draw(*c);
	for (auto &c : players)
		window.draw(*c);
	for (auto &coll_mesh : collisions)
	{
		for (auto &meshes : coll_mesh.get()->get_collmesh())
		{
			sf::RectangleShape shape(sf::Vector2f(static_cast<float>(meshes.width), static_cast<float>(meshes.height)));
			shape.setPosition(static_cast<float>(meshes.left), static_cast<float>(meshes.top));
			shape.setFillColor(sf::Color(255, 0, 0, 82));
			window.draw(shape);
		}
	}
	for (auto &c : texts)
		window.draw(*c);

	console->draw();

	window.display();
}