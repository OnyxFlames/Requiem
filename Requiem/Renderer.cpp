#include "Renderer.hpp"

void render_thread_function(Application *application)
{
	// It's frowned upon to force framerate limits, make it an option
	//application->get_window().setFramerateLimit(144);
	try
	{

		sf::Texture loading, sfml;
		if (!loading.loadFromFile("../resources/loading1.png") || !sfml.loadFromFile("../resources/logos/sfml-logo-small.png"))
		{
			std::cout << "Error loading initial textures! :/\n";
		}
		sf::Sprite loading_sprite, sfml_sprite;
		loading_sprite.setTexture(loading);
		//loading_sprite.setPosition(-app->get_players()[0]->getPosition().x, -app->get_players()[0]->getPosition().y);
		loading_sprite.setPosition(0.f, 0.f);
		sfml_sprite.setTexture(sfml);
		sfml_sprite.setPosition((application->get_window_size().x / 2) - (sfml_sprite.getGlobalBounds().width / 2),
			(application->get_window_size().y / 2) - (sfml_sprite.getGlobalBounds().height / 2));

		application->get_window().clear(sf::Color::Black);
		application->get_window().draw(sfml_sprite);
		application->get_window().display();

		sf::sleep(sf::seconds(1.0f));

		application->get_window().clear();
		application->get_window().draw(loading_sprite);
		application->get_window().display();

		sf::sleep(sf::seconds(2.5f));

		while (application->get_window().isOpen() && !application->get_state().empty())
			application->get_state().top()->draw();
	}
	catch (std::exception e)
	{
		std::cerr << "[Thread: Renderer]:" << e.what() << std::endl;
	}
}
