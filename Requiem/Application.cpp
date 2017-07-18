#include "Application.hpp"
#include "Renderer.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

#include "build_info.hpp" // Debug_Utils.hpp included here

#include "States/Playing_State.hpp"

/*
TEST CODE
*/
#include "Maps/Tilemap.hpp"
#include "build_info.hpp"
#include "ResourceManagers/TextureManager.hpp"

#include "AnimatedSprite.hpp"
/*...*/


/*
*	Somewhere where it allocates resources, the game state isn't getting the right ones
*	POTENTIAL FIXES
	*	Make the draw loop check if there's any current states, otherwise don't attempt to draw.
	*	Figure out better ways to prepare and add states to the game, maybe make the game push a default (loading) state before pushing the new gameplay state.
*
*/

Application::Application()
	: window(sf::VideoMode(DEFAULT_SCREENWIDTH, DEFAULT_SCREENHEIGHT), "Game Demo"), render_thread(&render_thread_function, this)
{	

	/*Game State Test Code*/
	/*
	TextureManager tm;
	tm.load(TextureID::City, "../resources/textures/roguelikeCity_transparent.png");
	tm.load(TextureID::Cave, "../resources/textures/roguelikeDungeon_transparent.png");
	tm.load(TextureID::Characters, "../resources/textures/roguelikeChar_transparent.png");

	sf::Sprite player;
	player.setTexture(tm.get(TextureID::Characters));
	player.setTextureRect(sf::IntRect(0, 0, 16, 16));

	Tilemap squares;
	squares.load_from_file("../resources/maps/Squares.rmap");
	squares.set_texture(tm.get(TextureID::City));

	Tilemap lake;
	lake.set_texture(tm.get(TextureID::Cave));
	lake.load_from_file("../resources/maps/Lake.rmap");

	Tilemap dirtpath;
	dirtpath.set_texture(tm.get(TextureID::City));
	dirtpath.load_from_file("../resources/maps/DirtPath.rmap");

	Tilemap fountain;
	fountain.set_texture(tm.get(TextureID::City));
	fountain.load_from_file("../resources/maps/DevTest.rmap");

	AnimatedSprite anim;
	anim.setTexture(tm.get(TextureID::Characters));
	anim.setPosition(256, 128);
	anim.load_from_file("../resources/animations/PlayerWeaponSwap.anim");

	AnimatedSprite weapon_changer;
	weapon_changer.setTexture(tm.get(TextureID::Characters));
	weapon_changer.setPosition(288, 128);
	weapon_changer.load_from_file("../resources/animations/PlayerWeaponSwap.anim");

	CollisionMesh coll;
	coll.load_from_file("../resources/meshes/OutsideBounds.coll");
	*/
	pushState(std::make_unique<Playing_State>(*this));
	/*
	get_state().top()->add_player(std::make_unique<sf::Sprite>(player));
	//get_state().top()->add_a_sprite(std::make_unique<AnimatedSprite>(anim));
	//get_state().top()->add_a_sprite(std::make_unique<AnimatedSprite>(weapon_changer));
	get_state().top()->add_collisionmesh(std::make_unique<CollisionMesh>(coll));

	get_state().top()->add_tilemap(fountain.get_map());
	get_state().top()->add_tilemap(dirtpath.get_map());
	get_state().top()->add_tilemap(lake.get_map());
	get_state().top()->add_tilemap(squares.get_map());
	*/

	// Text stuff was removed here.

	if (get_state().top()->get_texts().size() < 5)
	{
		// Display the amount of texts that failed to load. Right now we're adding 5 so subtracts the vectors size from 5.
		//std::cout << "Failed to load text: " << (5 - get_state().top()->get_texts().size()) << "/5 failed\n";
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
			std::string command = "";
			switch (event.type)
			{
				/*-Non-keyboard input based events-*/
			case sf::Event::Closed:
				exit_render = true;
				std::cout << "[App] Waiting on render thread to close...\n";
				render_thread.wait(); break;
				window.close();
				break;
			case sf::Event::Resized:
				window.setSize({ event.size.width, event.size.height });
				texts.at(build_info)->setString("Build v" + BUILD_VERSION_MAJOR + "." + BUILD_VERSION_MINOR + "\nResolution: " + (std::to_string(window.getSize().x) + "x" + std::to_string(window.getSize().y)));
				break;
				/*-Key Pressed Events*/
		case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						exit_render = true;
						std::cout << "Waiting on render thread to close...\n";
						render_thread.wait();
						window.close();
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
						handle_command(command);
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
					clickSpot.setPosition(0.f, 0.f);
					clickSpot.move(event.mouseButton.x - clickSpot.getGlobalBounds().width / 2,
											event.mouseButton.y - clickSpot.getGlobalBounds().height / 2);
					break;
				}
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
		return;
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

	buff << "Objects: " << get_obj_count();

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

	window.setView(camera);

}

void Application::run()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		//std::cout << "In run loop\n";
		states.top()->input();
		states.top()->update(clock.restart());
		//states.top()->draw();
		//input();
		//update(clock.restart());
	}
}
Application::~Application()
{
}
