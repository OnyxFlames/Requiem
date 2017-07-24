#include "Application.hpp"
#include "Renderer.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

#include "build_info.hpp" // Debug_Utils.hpp included here

/*
TEST CODE
*/
#include "Maps/Tilemap.hpp"
#include "build_info.hpp"
#include "ResourceManagers/TextureManager.hpp"

#include "AnimatedSprite.hpp"

Application::Application()
	: window(sf::VideoMode(DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT), "Game Demo"), render_thread(&render_thread_function, this)
{	
	// load config information
	sf::Vector2u dimensions = { DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT };
	std::ifstream lua("../resources/config.lua");
	if (!lua.is_open())
	{
		std::cerr << "[Lua] Failed to find lua.config! Running with defaults.\n";
	}
	else
	{
		lua.close();
		luaL_dofile(L, "../resources/config.lua");
		lua_getglobal(L, "width");
		if (lua_isnumber(L, 1) == 0)
		{
			std::cerr << "[Lua] Config file error! 'width' is not an integer.\n";
			lua_pop(L, 1);
		}
		else
		{
			dimensions.x = (unsigned)lua_tonumber(L, 1);
			lua_pop(L, 1);
		}
		lua_getglobal(L, "height");
		if (lua_isnumber(L, 1) == 0)
		{
			std::cerr << "[Lua] Config file error! 'height' is not an integer.\n";
			lua_pop(L, 1);
		}
		else
		{
			dimensions.y = (unsigned)lua_tonumber(L, 1);
			lua_pop(L, 1);
		}
		
		window.setSize(dimensions);
		camera.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));

	}


	window.setActive(false);
	render_thread.launch();
}

void Application::input()
{
	if (window.isOpen())
	{
		if(window.pollEvent(event))
		{
			//std::string command = "";
			switch (event.type)
			{
				/*-Non-keyboard input based events-*/
			case sf::Event::Closed:
				exit_render = true;
				std::cout << "[App] Waiting on render thread to close...\n";
				window.close();
				render_thread.wait();
				break;
			case sf::Event::Resized:
				window.setSize({ event.size.width, event.size.height });
				texts.at(build_info)->setString("Build v" + BUILD_VERSION_MAJOR + "." + BUILD_VERSION_MINOR + "\nResolution: " + (std::to_string(window.getSize().x) + "x" + std::to_string(window.getSize().y)));
				camera.setSize({ (float)event.size.width, (float)event.size.height });
				break;
				/*-Key Pressed Events*/
		case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						exit_render = true;
						std::cout << "[App] Waiting on render thread to close...\n";
						window.close();
						render_thread.wait();
						break;
					case sf::Keyboard::W:
						m_moveup = true;
						break;
					case sf::Keyboard::A:
						m_moveleft = true;
						break;
					case sf::Keyboard::S:
						m_movedown = true;
						break;
					case sf::Keyboard::D:
						m_moveright = true;
						break;
					case sf::Keyboard::I:
						camera.zoom(0.5f);
#ifdef DEBUG
						std::cout << "Zoom in to: ";
						std::cout << camera.getSize().x << "x" << camera.getSize().y << "\n";
#endif
						break;
					case sf::Keyboard::O:
						camera.zoom(2.f);
#ifdef DEBUG
						std::cout << "Zoomout to: ";
						std::cout << camera.getSize().x << "x" << camera.getSize().y << "\n";
#endif
						break;
					case sf::Keyboard::P:
						camera_follow_player = !camera_follow_player;
						std::cout << "Following player: " << std::boolalpha << camera_follow_player << "\n";
						break;
					case sf::Keyboard::U:
						std::cout << "Reset camera values.\n";
						if (camera_follow_player)
							camera_follow_player = false;

						while (camera.getSize().x > window.getSize().x)
							camera.zoom(0.5f);
						while (camera.getSize().x < window.getSize().x)
							camera.zoom(2.f);
						break;
					case sf::Keyboard::T:
						std::cout << "> ";
						//handle_command(command);
						break;
#ifdef DEBUG	/*Debug for dialog box testing*/

					case sf::Keyboard::B:
						std::cout << "Updating dialog box...\n";
						updateDialogBox = true;
						/*the updateDialogBox variable is using in Render.cpp to update the box bounds and position for the dialog box.(will eventually turn into a class)*/
						break;

#endif
#ifdef DEBUG	/*Debug for keycode testing*/
					default:
						std::cerr << "Unknown keycode: " << event.key.code << "\n";
#endif
				}
				break;
				/*-Key Released Events*/
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						std::cout << "Closing lag? This shouldn't happen!\n";
						break;
					case sf::Keyboard::W:
						m_moveup = false;
						break;
					case sf::Keyboard::A:
						m_moveleft = false;
						break;
					case sf::Keyboard::S:
						m_movedown = false;
						break;
					case sf::Keyboard::D:
						m_moveright = false;
						break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					break;
				}
				break;
			
			}
		}
	}
}

bool Application::check_collision(sf::Vector2f pos, sf::Time dt, uint8_t direction)
{
	switch (direction)
	{
		case 'U':
			pos.y -= (move_speed * dt.asMicroseconds());
		break;
		case 'L':
			pos.x -= (move_speed * dt.asMicroseconds());
			break;
		case 'D':
			pos.y += (move_speed * dt.asMicroseconds());
			break;
		case 'R':
			pos.x += (move_speed * dt.asMicroseconds());
			break;
		default:
			std::cerr << "Error: Unknown direction\n";
			break;
	}
	// In list of collision meshes
	for (auto &coll : collisions)
	{
		// For each rectangle in the mesh
		for (auto &collmesh : coll.get()->get_collmesh())
		{
			if (collmesh.intersects(sf::IntRect(static_cast<int>(pos.x), static_cast<int>(pos.y), 16, 16)))
				return true;
		}
	}
	return false;
}

void Application::update(sf::Time dt)
{
	static sf::Time accum;
	accum += dt;
	
	if (accum <= time_step)
		return;

	dt = accum;
	accum = sf::seconds(0);
	static sf::Time frame_count;
	static unsigned int frames = 0;
	if (frame_count <= sf::milliseconds(1000))
	{
		frames++;
		frame_count += dt;
	}
	else
	{
		texts[logic_rate].get()->setString("Logic rate: \t" + std::to_string(frames));
		frame_count = sf::seconds(0.f);
		frames = 0;
		//return;
	}
	/*If the game is paused, change the delta to 0 for updates*/
	if (is_paused)
		dt = sf::milliseconds(0);

	// Don't bother updating, there's no players loaded.
	// If this like wasn't here, the game would crash
	if (players.size() < 1)
		return;


	if (m_moveup)
	{
		if (check_collision(players.at(0)->getPosition(), dt, 'U'))
			if(debug_noclip)
				players.at(0)->move(0.f, -(move_speed * dt.asMicroseconds()));
			else
				;
		else
			players.at(0)->move(0.f, -(move_speed * dt.asMicroseconds()));
	}
	if (m_moveleft)
	{
		if (check_collision(players.at(0)->getPosition(), dt, 'L'))
			if (debug_noclip)
				players.at(0)->move(-(move_speed * dt.asMicroseconds()), 0.f);
			else
				;
		else
			players.at(0)->move(-(move_speed * dt.asMicroseconds()), 0.f);
	}
	if (m_movedown)
	{
		if (check_collision(players.at(0)->getPosition(), dt, 'D'))
			if (debug_noclip)
				players.at(0)->move(0.f, move_speed * dt.asMicroseconds());
			else
				;
		else
			players.at(0)->move(0.f, move_speed * dt.asMicroseconds());
	}
	if (m_moveright)
	{
		if (check_collision(players.at(0)->getPosition(), dt, 'R'))
			if (debug_noclip)
				players.at(0)->move(move_speed * dt.asMicroseconds(), 0.f);
			else
				;
		else
			players.at(0)->move(move_speed * dt.asMicroseconds(), 0.f);
	}

	std::stringstream buff;
	buff << "<" << std::setprecision(3) << std::fixed << players.at(0)->getPosition().x << "," << players.at(0)->getPosition().y << ">" << std::setprecision(6);
	texts.at(player_pos)->setString(buff.str());

	buff.str("");

	texts.at(objects)->setString(buff.str());
	texts.at(objects)->setPosition(
		window.getSize().x - (texts.at(objects)->getGlobalBounds().width + 10.f),
		texts.at(objects)->getPosition().y
	);

	if(camera_follow_player)
		camera.setCenter(
			players[0].get()->getPosition().x + (players[0].get()->getGlobalBounds().width/2),
			players[0].get()->getPosition().y + (players[0].get()->getGlobalBounds().height/2));
	else
		camera.setCenter(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2));

	for (auto &asprite : a_sprites)
		asprite->update(dt);

	const sf::Vector2f text_spacing = { 0.5f, 17.5f };
	texts.at(logic_rate)->setPosition(getHUD(camera));
	texts.at(graphic_rate)->setPosition(getHUD(camera) + text_spacing);
	texts.at(build_info)->setPosition(getHUD(camera) + text_spacing + text_spacing);
	texts.at(player_pos)->setPosition(getHUD(camera) + text_spacing + text_spacing + text_spacing + text_spacing);

	window.setView(camera);

}

void Application::run()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		input();
		update(clock.restart());
	}
}
Application::~Application()
{
	std::clog << "[App] Destroying app.\n";
}
