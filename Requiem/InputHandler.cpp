#include "InputHandler.hpp"

#include "build_info.hpp"


InputHandler::InputHandler(Application &_app)
{
	app = &_app;
}


InputHandler::~InputHandler()
{
}

InputMode InputHandler::getMode()
{
	return mode;
}

void InputHandler::handle(sf::Event &e)
{
	switch (mode)
	{
	case InputMode::menu:
		handle_menu_input(e);
		break;
	case InputMode::console:
		handle_console_input(e);
		break;
	case InputMode::game:
		handle_game_input(e);
		break;
	}
}

void InputHandler::handle_menu_input(sf::Event &e)
{

}
void InputHandler::handle_console_input(sf::Event &e)
{
	sf::RenderWindow& window = app->get_window();
	if (window.isOpen())
	{
		if (window.pollEvent(e))
		{
			//std::string command = "";
			switch (e.type)
			{
			case sf::Event::Closed:
				app->exit_render = true;
				std::cout << "[App] Waiting on render thread to close...\n";
				window.close();
				app->render_thread.wait();
				break;
			case sf::Event::KeyPressed:
				switch (e.key.code)
				{
				case sf::Keyboard::Return:
					if (app->console->is_active())
						app->console->execute();
					app->console->toggle();
					mode = game;
					break;
				}
				break;
			case sf::Event::TextEntered:
				if (app->console->is_active())
					app->console->update_string(e.text.unicode);
				break;
			}
		}
	}
}
void InputHandler::handle_game_input(sf::Event &e)
{
	sf::RenderWindow& window = app->get_window();
	if (window.isOpen())
	{
		if (window.pollEvent(e))
		{
			//std::string command = "";
			switch (e.type)
			{
				/*-Non-keyboard input based events-*/
			case sf::Event::Closed:
				app->exit_render = true;
				std::cout << "[App] Waiting on render thread to close...\n";
				window.close();
				app->render_thread.wait();
				break;
			case sf::Event::Resized:
				window.setSize({ e.size.width, e.size.height });
				app->texts.at(build_info)->setString("Build v" + BUILD_VERSION_MAJOR + "." + BUILD_VERSION_MINOR + "\nResolution: " + (std::to_string(window.getSize().x) + "x" + std::to_string(window.getSize().y)));
				app->camera.setSize({ (float)e.size.width, (float)e.size.height });
				break;
				/*-Key Pressed Events*/
			case sf::Event::KeyPressed:
				switch (e.key.code)
				{
				case sf::Keyboard::Return:
					if (app->console->is_active())
						app->console->execute();
					app->console->toggle();
					mode = console;
					break;
				case sf::Keyboard::Escape:
					app->exit_render = true;
					std::cout << "[App] Waiting on render thread to close...\n";
					window.close();
					app->render_thread.wait();
					break;
				case sf::Keyboard::W:
					app->m_moveup = true;
					break;
				case sf::Keyboard::A:
					app->m_moveleft = true;
					break;
				case sf::Keyboard::S:
					app->m_movedown = true;
					break;
				case sf::Keyboard::D:
					app->m_moveright = true;
					break;
				case sf::Keyboard::I:
					app->camera.zoom(0.5f);
#ifdef DEBUG
					//std::cout << "Zoom in to: ";
					//std::cout << camera.getSize().x << "x" << camera.getSize().y << "\n";
#endif
					break;
				case sf::Keyboard::O:
					app->camera.zoom(2.f);
#ifdef DEBUG
					//std::cout << "Zoomout to: ";
					//std::cout << camera.getSize().x << "x" << camera.getSize().y << "\n";
#endif
					break;
				case sf::Keyboard::P:
					if (!app->console->is_active())
						app->camera_follow_player = !app->camera_follow_player;
					//std::cout << "Following player: " << std::boolalpha << camera_follow_player << "\n";
					break;
				case sf::Keyboard::U:
					//std::cout << "Reset camera values.\n";
					if (app->camera_follow_player)
						app->camera_follow_player = false;

					while (app->camera.getSize().x > window.getSize().x)
						app->camera.zoom(0.5f);
					while (app->camera.getSize().x < window.getSize().x)
						app->camera.zoom(2.f);
					break;
				}
				break;
				/*-Key Released Events*/
			case sf::Event::KeyReleased:
				switch (e.key.code)
				{
				case sf::Keyboard::Escape:
					std::cout << "Closing lag? This shouldn't happen!\n";
					break;
				case sf::Keyboard::W:
					app->m_moveup = false;
					break;
				case sf::Keyboard::A:
					app->m_moveleft = false;
					break;
				case sf::Keyboard::S:
					app->m_movedown = false;
					break;
				case sf::Keyboard::D:
					app->m_moveright = false;
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (e.mouseButton.button)
				{
				case sf::Mouse::Left:
					break;
				}
				break;
			}
		}
	}
}