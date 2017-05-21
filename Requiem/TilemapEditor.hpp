#pragma once
#include "Maps/Tilemap.hpp"

class TilemapEditor : public Tilemap
{
public:
	void change_tile(sf::Vector2f pos, sf::Vector2f coords)
	{
		get_data()[(int)pos.x][(int)pos.y].x = coords.x;
		get_data()[(int)pos.x][(int)pos.y].y = coords.y;
	}
	TilemapEditor();
	~TilemapEditor();
};

