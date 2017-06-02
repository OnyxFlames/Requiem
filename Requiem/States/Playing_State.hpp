#pragma once
#include <memory>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Game_State.hpp"

#include "../Debug_Utils.hpp"

#include "../ResourceManagers/TextureManager.hpp"

#include "../AnimatedSprite.hpp"

#include "../CollisionMesh.hpp"

#include "../DialogBox.hpp"

#include "../Builtins.hpp"

#include "../Application.hpp"

class Playing_State : public Game_State
{
public:
	Playing_State(Application &_app)
		: Game_State(_app)
	{
		//std::cout << "Game state created at 0x" << this << " (" << sizeof(Playing_State) << " bytes)\n";
		//std::cout << "Setting default camera\n";
		camera = app->get_window().getView();
	}

	virtual void input() override;
	virtual void update(sf::Time dt) override;
	virtual void draw() override;

	// Loading helper functions. Defined in Application_loading.cpp
	virtual void add_tilemap(std::unique_ptr<sf::Sprite> _tilemap) override;
	virtual void add_player(std::unique_ptr<sf::Sprite> _player) override;
	virtual void add_a_sprite(std::unique_ptr<AnimatedSprite> _a_sprite) override;
	virtual void add_collisionmesh(std::unique_ptr<CollisionMesh> coll_mesh) override;
	virtual void add_dialog(std::unique_ptr<DialogBox> dialog_box) override;
	virtual void add_text(std::unique_ptr<sf::Text> text) override;
	// Rendering helper functions. Defined in Application_render.cpp
	virtual sf::RenderWindow& get_window() override;
	virtual const std::vector<std::unique_ptr<sf::Sprite>>& get_maps() override;
	virtual const std::vector<std::unique_ptr<sf::Sprite>>& get_sprites() override;
	virtual const std::vector<std::unique_ptr<sf::Sprite>>& get_players() override;
	virtual const std::vector<std::unique_ptr<AnimatedSprite>>& get_a_sprites() override;
	virtual const std::vector<std::unique_ptr<sf::Text>>& get_texts() override;
	virtual const std::vector<std::unique_ptr<CollisionMesh>>& get_collmeshes() override;
	virtual const std::vector <std::unique_ptr<DialogBox>>& get_dialogs() override;
	bool check_collision(sf::Vector2f pos, sf::Time dt, uint8_t direction);
	size_t get_obj_count();

private:
	const sf::Time time_step = sf::seconds(1.0f / 61.5f);
	bool m_moveup = false, m_moveleft = false, m_movedown = false, m_moveright = false;
	bool camera_follow_player = false;
	bool is_paused = false;
	bool debug_noclip = false;
	//Note: Once the camera class is added this will be phased out
	sf::View camera;

	std::vector<std::unique_ptr<sf::Sprite>> players;
	std::vector<std::unique_ptr<sf::Sprite>> tilemaps;
	std::vector<std::unique_ptr<AnimatedSprite>> a_sprites;
	std::vector<std::unique_ptr<sf::Sprite>> sprites;
	std::vector<std::unique_ptr<CollisionMesh>> collisions;
	std::vector<std::unique_ptr<DialogBox>> dialogs;
	std::vector<std::unique_ptr<sf::Text>> texts;
};

