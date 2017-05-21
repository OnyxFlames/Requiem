#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "../AnimatedSprite.hpp"
#include "../CollisionMesh.hpp"
#include "../DialogBox.hpp"

//#include "../Application.hpp"

class Application;

class Game_State
{

public:
	Game_State(Application &_app);
	
	virtual void input() = 0;
	virtual void update(sf::Time dt) = 0;
	virtual void draw() = 0;

	virtual void add_tilemap(std::unique_ptr<sf::Sprite> _tilemap) = 0;
	virtual void add_player(std::unique_ptr<sf::Sprite> _player) = 0;
	virtual void add_a_sprite(std::unique_ptr<AnimatedSprite> _a_sprite) = 0;
	virtual void add_collisionmesh(std::unique_ptr<CollisionMesh> coll_mesh) = 0;
	virtual void add_dialog(std::unique_ptr<DialogBox> dialog_box) = 0;
	virtual void add_text(std::unique_ptr<sf::Text> text) = 0;
	// Rendering helper functions. Defined in Application_render.cpp
	virtual sf::RenderWindow& get_window() = 0;
	virtual const std::vector<std::unique_ptr<sf::Sprite>>& get_maps() = 0;
	virtual const std::vector<std::unique_ptr<sf::Sprite>>& get_sprites() = 0;
	virtual const std::vector<std::unique_ptr<sf::Sprite>>& get_players() = 0;
	virtual const std::vector<std::unique_ptr<AnimatedSprite>>& get_a_sprites() = 0;
	virtual const std::vector<std::unique_ptr<sf::Text>>& get_texts() = 0;
	virtual const std::vector<std::unique_ptr<CollisionMesh>>& get_collmeshes() = 0;
	virtual const std::vector<std::unique_ptr<DialogBox>>& get_dialogs() = 0;

	virtual size_t get_obj_count() = 0;

protected:
	Application *app;
};