#include "Renderer.hpp"

void render_thread_function(Application *application)
{
	// It's frowned upon to force framerate limits, make it an option
	//application->get_window().setFramerateLimit(144);
	try
	{
		sf::RenderWindow& win = application->get_window();
		sf::Texture loading, sfml;
		if (!loading.loadFromFile("../resources/loading1.png") || !sfml.loadFromFile("../resources/logos/sfml-logo-small.png"))
		{
			std::cout << "Error loading initial textures! :/\n";
		}
		sf::Sprite loading_sprite, sfml_sprite;
		loading_sprite.setTexture(loading);
		loading_sprite.setPosition(0.f, 0.f);
		sfml_sprite.setTexture(sfml);
		sfml_sprite.setPosition((application->get_window_size().x / 2) - (sfml_sprite.getGlobalBounds().width / 2),
			(win.getSize().y / 2) - (sfml_sprite.getGlobalBounds().height / 2));

		win.clear(sf::Color::Black);
		win.draw(sfml_sprite);
		win.display();

		sf::sleep(sf::seconds(1.0f));

		win.clear();
		win.draw(loading_sprite);
		win.display();

		sf::sleep(sf::seconds(2.5f));


		win.clear(sf::Color::Cyan);
		while (win.isOpen())
			application->render();
	}
	catch (std::exception e)
	{
		std::cerr << "[Thread: Renderer]:" << e.what() << std::endl;
	}
}
