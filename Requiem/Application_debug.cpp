#include "Application.hpp"


/*void Application::handle_command(std::string &_command)
{
	while (_command != "resume")
	{
		std::cin >> _command;
		if (_command == "exit")
		{
			window.close();
			break;
		}
		else if (_command == "help")
		{
			std::cout << "Available commands: \n"
				"resume\n"
				"exit\n"
				"removemap\n"
				"teleport\n"
				"noclip\n"
				"setres\n"
				"movemap\n"
				"> ";
		}
		else if (_command == "removemap")
		{
			std::cout << "Enter map ID(Warning, may crash): ";
			std::cin >> _command;
			if (static_cast<unsigned>(std::stoi(_command)) < tilemaps.size())
			{
				tilemaps.erase(tilemaps.begin() + std::stoi(_command));
				std::cout << "Map removed!\n";
			}
			else
				std::cout << "Map ID not found!\n";
			break;
		}
		else if (_command == "teleport")
		{
			float x = 0, y = 0;
			std::cin >> _command;
			x = std::stof(_command);
			std::cin >> _command;
			y = std::stof(_command);
			players[0].get()->setPosition(x, y);
			std::cout << "Teleported to <" << x << "," << y << ">\n";
			break;
		}
		else if (_command == "noclip")
		{
			debug_noclip = !debug_noclip;
			if (debug_noclip)
				std::cout << "Removed collision.\n";
			else
				std::cout << "Restored collision.\n";
			break;
		}
		else if (_command == "setres")
		{
			sf::Vector2u newsize{0u, 0u};
			std::cin >> _command;
			newsize.x = std::stoi(_command);
			std::cin >> _command;
			newsize.y = std::stoul(_command);
			window.setSize(newsize);
			std::cout << "Window size set to " << newsize.x << "x" << newsize.y <<"\n";
			break;
		}
		else if (_command == "movemap")
		{
			size_t mapid;
			std::cin >> _command;
			mapid = static_cast<size_t>(std::stoi(_command));

			float x = 0, y = 0;
			std::cin >> _command;
			x = std::stof(_command);
			std::cin >> _command;
			y = std::stof(_command);

			if (mapid < tilemaps.size())
			{
				tilemaps.at(mapid)->setPosition({x, y});
				std::cout << "Map moved!\n";
			}
			else
				std::cout << "Map ID not found!\n";
			break;
		}
	}
	std::cout << "Resuming play.\n";
}

size_t Application::get_obj_count()
{
	size_t count = 0;
	count = get_a_sprites().size() +
		get_collmeshes().size() +
		get_dialogs().size() +
		get_maps().size() +
		get_players().size() +
		get_sprites().size() +
		get_texts().size();
	return count;
}*/