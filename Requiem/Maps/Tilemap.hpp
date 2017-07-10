#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>

#include "../Debug_Utils.hpp"

class Tilemap
{
private:
	//const float ti = 1.063f;			// The space needed between tiles so pixels are rounded and skipped. (ti = 'tile increment')
	const float ti = 1.0625f;
	const unsigned char tilesize = 16U;	// The size of each individual tile in a given spritesheet.
	sf::Texture spritesheet;
	//2D Array of map data
	sf::Vector2f pos = sf::Vector2f(0, 0);
	unsigned map_width, map_height;
	std::vector<std::vector<sf::Vector2f>> data;
	std::unique_ptr<sf::Texture> map_finished;
	//void load_data2(std::ifstream &file); // Possibly allow tilemaps to have multiple layers of tiles.
public:
	Tilemap();
	Tilemap& operator=(const Tilemap&) = delete;
	bool load_from_file(const std::string &filename);
	void set_position(sf::Vector2f& _pos)
	{
		pos = _pos;
	}
	void set_texture(const sf::Texture texture) 
	{
		spritesheet = texture;
	}
	//TODO: Remove the code that draws the map to a rendertexture into the generate_map() function
	std::unique_ptr<sf::Texture> generate_map()
	{
		return std::move(map_finished);
	}
	//TODO pt2: make get_map return the generated texture as a sprite if it doesnt need updating(if set map hasnt been called since last generation)
	// If it needs updating, call generate_map() internally then return the finished result.
	std::unique_ptr<sf::Sprite> get_map();
	void set_map(unsigned _width, unsigned _height, std::vector<std::vector<sf::Vector2f>> &_coords);
	std::vector<std::vector<sf::Vector2f>>& get_data() { return data; }
	// This gives the map a 128x128 array of -1's, allowing the map editor to change whatever tile it wants without risking going out of bounds
	void construct_map() 
	{
		map_width = 128; map_height = 128;
		for (unsigned h = 0; h < map_height; h++)
		{
			std::vector<sf::Vector2f> vecbuff;
			for (unsigned w = 0; w < map_width; w++)
			{
				vecbuff.push_back(sf::Vector2f(-1, -1));
			}
			data.push_back(vecbuff);
		}
	}
	~Tilemap();
};

