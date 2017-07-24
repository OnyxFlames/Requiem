#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include <vector>
#include <stack>
#include <iostream>

#include "Debug_Utils.hpp"

#include "ResourceManagers/TextureManager.hpp"

#include "AnimatedSprite.hpp"

#include "CollisionMesh.hpp"

#include "DialogBox.hpp"

#include "Lua_Main.hpp"

#include "Builtins.hpp"

/*
enum builtins_index : unsigned char
{
	graphic_rate = 0,
	logic_rate = 1,
	build_info = 2,
	player_pos = 3,
	objects = 4,
};
*/
#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

class Application
{
private:
	sf::View camera;
	sf::RenderWindow window;
	sf::Thread render_thread;
	
	std::vector<std::unique_ptr<sf::Sprite>> players;
	std::vector<std::unique_ptr<sf::Sprite>> tilemaps;
	std::vector<std::unique_ptr<AnimatedSprite>> a_sprites;
	std::vector<std::unique_ptr<sf::Sprite>> sprites;
	std::vector<std::unique_ptr<CollisionMesh>> collisions;
	std::vector<std::unique_ptr<DialogBox>> dialogs;
	std::vector<std::unique_ptr<sf::Text>> texts;
	
	sf::Color void_color = sf::Color(0, 0, 0);

	sf::Event event;

	sf::Font default_font;

	lua_State *L = init_lua();
	
	bool is_fullscreen = false;
	/*
		99% of the time with will be true, but keep this stored just in case there's a client that runs single threaded
		(Doubt performance would be decent enough but alas)
	*/
	bool is_multithreaded = true;

	void input();
	// Fixed logical update rate. Averages out to 58-60 updates/sec
	const sf::Time time_step = sf::seconds(1.0f / 60.f);//sf::seconds(1.0f / 61.5f);
	void update(sf::Time dt);
	//movement flags
	const float move_speed = 0.00015f;
	bool m_moveup = false, m_moveleft = false, m_movedown = false, m_moveright = false;
	bool camera_follow_player = false;

	bool check_collision(sf::Vector2f pos, sf::Time dt, uint8_t direction);
	/*Debug functions and data members*/
	//void handle_command(std::string &_command);
	bool debug_noclip = false;
public:
	void render();
	sf::Vector2f getHUD()
	{
		return
		{ 
			camera.getCenter().x - camera.getSize().x / 2,
			camera.getCenter().y - camera.getSize().y / 2
		};
	}
	sf::Vector2f getHUD(sf::View &camera)
	{
		return
		{
			camera.getCenter().x - camera.getSize().x / 2,
			camera.getCenter().y - camera.getSize().y / 2
		};
	}
	/*...*/

	/*Debug dialog box code*/
	bool updateDialogBox = false;
	/*...*/

	//bool is_loading = false;
	bool is_paused = false;
	// if the game is closing then let the render thread end first.
	bool exit_render = false;
	Application();
	~Application();
	void run();

	// Loading helper functions. Defined in Application_loading.cpp
	void add_tilemap(std::unique_ptr<sf::Sprite> _tilemap);
	void add_player(std::unique_ptr<sf::Sprite> _player);
	void add_a_sprite(std::unique_ptr<AnimatedSprite> _a_sprite);
	void add_collisionmesh(std::unique_ptr<CollisionMesh> coll_mesh);
	void add_dialog(std::unique_ptr<DialogBox> dialog_box);
	void add_text(std::unique_ptr<sf::Text> text);
	// Rendering helper functions. Defined in Application_render.cpp
	sf::RenderWindow& get_window();
	const sf::Vector2u get_window_size()
	{
		return window.getSize();
	}
	void close_render_thread(bool force = false)
	{
		if (is_multithreaded)
		{
			if (force)
				render_thread.terminate();
			else if (!force)
				render_thread.wait();
		}
	}
};

