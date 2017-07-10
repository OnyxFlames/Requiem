#include "TileMapManager.hpp"

class Tilemap;

TileMapManager::TileMapManager()
{
}


TileMapManager::~TileMapManager()
{
}

bool TileMapManager::load(TilemapID id, const std::string &filename)
{
	std::unique_ptr<Tilemap> tilemap(new Tilemap());
	if (!tilemap->load_from_file(filename))
		return false;
	else
		tilemaps.insert(std::make_pair(id, std::move(tilemap)));
	return true;
}
/* Broken
const Tilemap TileMapManager::get(TilemapID id)
{
	auto found = tilemaps.find(id);
	if (found == tilemaps.end())
	{
		std::cerr << "Error: could not find tilemap id " <<tilemap_names[id] << ". Tilemap data may be missing.\n";
		std::exit(-1);
	}
	else
	{
		return *found->second;
	}
	return;
}
*/