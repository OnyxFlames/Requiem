#include <iostream>

#include <SFML/Graphics.hpp>

#include "Application.hpp"
#include "Maps/Tilemap.hpp"
#include "build_info.hpp"
#include "ResourceManagers/TextureManager.hpp"

#include "AnimatedSprite.hpp"

#include "Debug_Utils.hpp"

#include "States/Playing_State.hpp"

int main(int argc, char* argv[])
{
	TextureManager tm;
	tm.load(TextureID::City, "../resources/textures/roguelikeCity_transparent.png");
	tm.load(TextureID::Cave, "../resources/textures/roguelikeDungeon_transparent.png");
	tm.load(TextureID::Characters, "../resources/textures/roguelikeChar_transparent.png");

	if (argc > 1)
	{
		if (std::strcmp(argv[1], "-h") == 0 || std::strcmp(argv[1], "--help") == 0)
		{
			std::cerr << "Game Demo build v" << BUILD_VERSION_MAJOR + "." + BUILD_VERSION_MINOR << "\n";
			std::cerr << "Compiled on: " << __DATE__ << " at " << __TIME__ << "\n";
#ifdef DEBUG
			std::cerr << BUILD_EDITION;
#endif
			std::cerr << "Can't launch? Contact jacobhicks123123@gmail.com\n";
			return 0;
		}
	}

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

	Application app;

	//app.pushState(std::make_unique<Playing_State>(app));

	app.get_state().top()->add_player(std::make_unique<sf::Sprite>(player));
	app.get_state().top()->add_a_sprite(std::make_unique<AnimatedSprite>(anim));
	app.get_state().top()->add_a_sprite(std::make_unique<AnimatedSprite>(weapon_changer));
	app.get_state().top()->add_collisionmesh(std::make_unique<CollisionMesh>(coll));
	
	//app.get_state().top()->add_text(std::make_unique<sf::Text>());

	app.get_state().top()->add_tilemap(fountain.get_map());
	app.get_state().top()->add_tilemap(dirtpath.get_map());
	app.get_state().top()->add_tilemap(lake.get_map());
	app.get_state().top()->add_tilemap(squares.get_map());


	sf::Text graphic_text;
	sf::Text logic_text;
	sf::Text build_info;
	sf::Text player_position;
	sf::Text objects;

	//camera = window.getView();
	sf::Font default_font;
	default_font.loadFromFile("../resources/fonts/consola.ttf");

	graphic_text.setFont(default_font);
	graphic_text.setFillColor(sf::Color::White);
	graphic_text.setScale(0.5f, 0.5f);
	graphic_text.setPosition(0.f, 0.f);

	logic_text.setFont(default_font);
	logic_text.setFillColor(sf::Color::White);
	logic_text.setScale(0.5f, 0.5f);
	logic_text.setPosition(0.f, 14.f);

	build_info.setFont(default_font);
	build_info.setFillColor(sf::Color::White);
	build_info.setScale(0.5f, 0.5f);
	build_info.setString("Build v" + BUILD_VERSION_MAJOR + "." + BUILD_VERSION_MINOR + "\nResolution: " + (std::to_string(app.get_window().getSize().x) + "x" + std::to_string(app.get_window().getSize().y)));
	build_info.setPosition(0.f, static_cast<float>(build_info.getGlobalBounds().height + 1.5f));

	player_position.setFont(default_font);
	player_position.setFillColor(sf::Color::Cyan);
	player_position.setScale(0.5f, 0.5f);
	player_position.setPosition(0.f, (build_info.getGlobalBounds().height + 2.f) * 2);

	objects.setFont(default_font);
	objects.setFillColor(sf::Color::Cyan);
	objects.setScale(0.5f, 0.5f);
	objects.setPosition(app.get_window().getSize().x - (objects.getGlobalBounds().width / 2), 0.f);


	//std::cout << "Attempted to add texts to current state\n";
	app.get_state().top()->add_text(std::make_unique<sf::Text>(logic_text));
	app.get_state().top()->add_text(std::make_unique<sf::Text>(graphic_text));
	app.get_state().top()->add_text(std::make_unique<sf::Text>(build_info));
	app.get_state().top()->add_text(std::make_unique<sf::Text>(player_position));
	app.get_state().top()->add_text(std::make_unique<sf::Text>(objects));


	//std::cout << "State object count: " << app.get_state().top()->get_obj_count() << "\n";
	try
	{
		app.run();
	}
	catch (std::exception e)
	{
		std::cerr << "[Thread: Logic]: " << e.what() << std::endl;
	}
	return 0;
}