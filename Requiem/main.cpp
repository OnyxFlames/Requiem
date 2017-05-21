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
		if (std::strcmp(argv[1], "--help") == 0)
		{
			std::cerr << "Game Demo build v" << BUILD_VERSION_MAJOR + "." + BUILD_VERSION_MINOR << "\n";
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

	app.pushState(std::make_unique<Playing_State>(app));

	app.get_state().top()->add_player(std::make_unique<sf::Sprite>(player));
	app.get_state().top()->add_a_sprite(std::make_unique<AnimatedSprite>(anim));
	app.get_state().top()->add_a_sprite(std::make_unique<AnimatedSprite>(weapon_changer));
	app.get_state().top()->add_collisionmesh(std::make_unique<CollisionMesh>(coll));
	
	app.get_state().top()->add_tilemap(fountain.get_map());
	app.get_state().top()->add_tilemap(dirtpath.get_map());
	app.get_state().top()->add_tilemap(lake.get_map());
	app.get_state().top()->add_tilemap(squares.get_map());

	std::cout << "State object count: " << app.get_state().top()->get_obj_count() << "\n";

	app.run();
	
	return 0;
}