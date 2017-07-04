#include "Playing_State.hpp"

#include "../Application.hpp"

#include "../build_info.hpp"

void Playing_State::input()
{
	if (app->get_window().isOpen())
	{
		sf::Event event;
		if (app->get_window().pollEvent(event))
		{
			std::string command = "";
			switch (event.type)
			{
				/*-Non-keyboard input based events-*/
			case sf::Event::Closed:
				app->exit_render = true;
				std::cout << "Waiting on render thread to close...\n";
				app->close_render_thread(true);
				app->get_window().close();
				break;
			case sf::Event::Resized:
				app->get_window().setSize({ event.size.width, event.size.height });
				//texts.at(build_info)->setString("Build v" + BUILD_VERSION_MAJOR + "." + BUILD_VERSION_MINOR + "\nResolution: " + (std::to_string(app->get_window().getSize().x) + "x" + std::to_string(app->get_window().getSize().y)));
				break;
				/*-Key Pressed Events*/
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					app->exit_render = true;
					std::cout << "Waiting on render thread to close...\n";
					app->close_render_thread(true);
					app->get_window().close();
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
					//camera.zoom(0.5f);
#ifdef DEBUG
					std::cout << "Zoom in unavailable in game state test\n";
					//std::cout << camera.getSize().x << "x" << camera.getSize().y << "\n";
#endif
					break;
				case sf::Keyboard::O:
					//camera.zoom(2.f);
#ifdef DEBUG
					std::cout << "Zoomout unavailable in game state test\n";
					//std::cout << camera.getSize().x << "x" << camera.getSize().y << "\n";
#endif
					break;
				case sf::Keyboard::P:
					camera_follow_player = !camera_follow_player;
					std::cout << "Following player: " << std::boolalpha << camera_follow_player << "\n";
					break;
				case sf::Keyboard::U:
					std::cout << "Camera buttons unavailable in game state test\n";
					if (camera_follow_player)
						camera_follow_player = false;

					//while (camera.getSize().x > app->get_window.getSize().x)
						//camera.zoom(0.5f);
					//while (camera.getSize().x < app->get_window.getSize().x)
						//camera.zoom(2.f);
					break;
				case sf::Keyboard::T:
					//std::cout << "> ";
					//handle_command(command);
					break;
#ifdef DEBUG	/*Debug for dialog box testing*/

				case sf::Keyboard::B:
					std::cout << "Updating dialog box...\n";
					//updateDialogBox = true;
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
					//clickSpot.setPosition(0.f, 0.f);
					//clickSpot.move(event.mouseButton.x - clickSpot.getGlobalBounds().width / 2,
						//event.mouseButton.y - clickSpot.getGlobalBounds().height / 2);
					break;
				}
			}
		}
	}
}
bool Playing_State::check_collision(sf::Vector2f pos, sf::Time dt, uint8_t direction)
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
void Playing_State::update(sf::Time dt)
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
		//@FIX
		//texts[logic_rate].get()->setString("Logic rate: \t" + std::to_string(frames));
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
			if (debug_noclip)
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
	/*
	std::stringstream buff;
	buff << "<" << std::setprecision(3) << std::fixed << players.at(0)->getPosition().x << "," << players.at(0)->getPosition().y << ">" << std::setprecision(6);
	texts.at(player_pos)->setString(buff.str());

	buff.str("");

	buff << "Objects: " << get_obj_count();

	texts.at(objects)->setString(buff.str());
	texts.at(objects)->setPosition(
		app->get_window().getSize().x - (texts.at(objects)->getGlobalBounds().width + 10.f),
		texts.at(objects)->getPosition().y
	);
	*/
	if (camera_follow_player)
		camera.setCenter(
			players[0].get()->getPosition().x + (players[0].get()->getGlobalBounds().width / 2),
			players[0].get()->getPosition().y + (players[0].get()->getGlobalBounds().height / 2));
	else
		;// camera.setCenter(static_cast<float>(app->get_window().getSize().x / 2), static_cast<float>(app->get_window().getSize().y / 2));

	for (size_t count = 0; count < get_a_sprites().size(); count++)
		get_a_sprites()[count]->update(dt);

	app->get_window().setView(camera);
}
void Playing_State::draw()
{
		/*
		sf::Texture loading, sfml;
		if (!loading.loadFromFile("../resources/loading1.png") || !sfml.loadFromFile("../resources/logos/sfml-logo-small.png"))
		{
			std::cout << "Error loading initial textures! :/\n";
		}
		sf::Sprite loading_sprite, sfml_sprite;
		loading_sprite.setTexture(loading);
		//loading_sprite.setPosition(-app->get_players()[0]->getPosition().x, -app->get_players()[0]->getPosition().y);
		sfml_sprite.setTexture(sfml);
		sfml_sprite.setPosition((app->get_window_size().x / 2) - (sfml_sprite.getGlobalBounds().width / 2),
			(app->get_window_size().y / 2) - (sfml_sprite.getGlobalBounds().height / 2));

		app->get_window().clear(sf::Color::Black);
		app->get_window().draw(sfml_sprite);
		app->get_window().display();
		
		//sf::sleep(sf::seconds(1.0f));
		
		app->get_window().clear();
		app->get_window().draw(loading_sprite);
		app->get_window().display();
		
		//sf::sleep(sf::seconds(2.5f));
		*/
		static sf::Clock timer;
		static sf::Time frame_count;
		static unsigned int frames = 0;
		if (app->exit_render)
			return;

			if (frame_count <= sf::milliseconds(1000))
			{
				frames++;
				frame_count += timer.restart();
			}
			else
			{
				frame_count = sf::seconds(0.f);
				if (app->is_paused)
					get_texts().at(graphic_rate)->setString("Graphic rate: " + std::to_string(frames) + " - paused");
				else
				{
					get_texts().at(graphic_rate)->setString("Graphic rate: " + std::to_string(frames));
				}
				frames = 0;
			}
			app->get_window().clear();
			for(size_t count = 0; count < get_maps().size(); count++)
			{
				//std::cout << "Drawing tilemap: " << count << "\n";
				app->get_window().draw(*get_maps()[count]);
			}
			for (size_t count = 0; count < get_sprites().size(); count++)
			{
				//std::cout << "Drawing sprite: " << count << "\n";
				app->get_window().draw(*get_sprites()[count]);
			}
#ifdef DEBUG
			for (auto &coll_mesh : get_collmeshes())
			{
				for (auto &meshes : coll_mesh.get()->get_collmesh())
				{
					sf::RectangleShape shape(sf::Vector2f(static_cast<float>(meshes.width), static_cast<float>(meshes.height)));
					shape.setPosition(static_cast<float>(meshes.left), static_cast<float>(meshes.top));
					shape.setFillColor(sf::Color(255, 0, 0, 82));
					app->get_window().draw(shape);
				}
			}
#endif
			//for (auto &player : app->get_players())
			for(size_t count = 0; count < get_players().size(); count++)
			{
				app->get_window().draw(*get_players()[count]);
			}
			//for (auto &a_sprite : app->get_a_sprites())
			for (size_t count = 0; count < get_a_sprites().size(); count++)
			{
				//app->get_window().draw(*get_a_sprites()[count]);
			}
			//for (auto &dialog : app->get_dialogs())
			{
				//if (dialog->isActive())
					//app->get_window().draw(dialog->get_dialog());
			}
			//std::cout << "Texts loaded: " << get_texts().size() << "\n";
			for (size_t count = 0; count < get_texts().size(); count++)
			{
				//std::cout << "Drawing text\n";
				app->get_window().draw(*get_texts()[count]);
			}
			app->get_window().display();
}

void Playing_State::add_tilemap(std::unique_ptr<sf::Sprite> _tilemap)
{
	tilemaps.push_back(std::move(_tilemap));
}
void Playing_State::add_player(std::unique_ptr<sf::Sprite> _player)
{
	players.push_back(std::move(_player));
}
void Playing_State::add_a_sprite(std::unique_ptr<AnimatedSprite> _a_sprite)
{
	a_sprites.push_back(std::move(_a_sprite));
}
void Playing_State::add_collisionmesh(std::unique_ptr<CollisionMesh> coll_mesh)
{
	collisions.push_back(std::move(coll_mesh));
}
void Playing_State::add_dialog(std::unique_ptr<DialogBox> dialog_box)
{
	dialogs.push_back(std::move(dialog_box));
}

void Playing_State::add_text(std::unique_ptr<sf::Text> text)
{
	//std::cout << "Texts vector size: " << get_texts().size() << "\n";
	//std::cout << "Contents: " << text->getString().toAnsiString() << "\n";
	texts.push_back(std::move(text));
}

sf::RenderWindow& Playing_State::get_window()
{
	return app->get_window();
}

const std::vector<std::unique_ptr<sf::Sprite>>& Playing_State::get_maps()
{
	//Note:
	//	You may be able to use this function to funnel out tilemaps within the windows view, and tilemaps that 
	//	are not by checking their bounds/size and seeing if it's currently within a given (configurable) range.
	return tilemaps;
}
const std::vector<std::unique_ptr<sf::Sprite>>& Playing_State::get_sprites()
{
	// See above note.
	return sprites;
}
const std::vector<std::unique_ptr<sf::Sprite>>& Playing_State::get_players()
{
	return players;
}
const std::vector<std::unique_ptr<AnimatedSprite>>& Playing_State::get_a_sprites()
{
	return a_sprites;
}
const std::vector<std::unique_ptr<sf::Text>>& Playing_State::get_texts()
{
	return texts;
}

const std::vector<std::unique_ptr<CollisionMesh>>& Playing_State::get_collmeshes()
{
	return collisions;
}

const std::vector <std::unique_ptr<DialogBox>>& Playing_State::get_dialogs()
{
	return dialogs;
}

size_t Playing_State::get_obj_count()
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
}