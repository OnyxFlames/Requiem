#pragma once

#include <map>
#include <memory>

#include "Maps/Tilemap.hpp"

static const char* tilemap_names[]
{
	"NoMap",
	"DevTest",
};

enum TilemapID
{
	NoMap,
	DevTest,
};

class TileMapManager
{
private:
	std::map<TilemapID, std::unique_ptr<Tilemap>> tilemaps;
public:
	TileMapManager();
	bool load(TilemapID id, const std::string &filename);
	const Tilemap get(TilemapID id);
	~TileMapManager();
};

