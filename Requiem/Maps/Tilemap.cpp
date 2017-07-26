#include "Tilemap.hpp"

Tilemap::Tilemap() 
	:	pos(sf::Vector2i(0, 0))
{
}


Tilemap::~Tilemap()
{
}


std::unique_ptr<sf::Sprite> Tilemap::get_map()
{
	sf::RenderTexture ret;
	if (!ret.create(static_cast<unsigned>((map_width * tilesize)), static_cast<unsigned>((map_height * tilesize))))
	{
		std::cerr << "Unable to create sf::RenderTexture for tilemap at X:" << pos.x << " Y:" << pos.y << "\n";
	}
#ifdef DEBUG
	//std::cerr << "Map size: " << map_width << "x" << map_height << "\n";
#endif
	sf::Sprite sprite;
	sprite.setTexture(spritesheet);
	ret.clear(sf::Color(0, 0, 255, 0));
	int x(0), y(0);
	for (auto i : data)
	{
		for (auto j : i)
		{
			//std::cout << "Tilemap: " << j.x * ti * tilesize << " " << j.y * ti * tilesize << "\n";
			sprite.setTextureRect(sf::IntRect(
				static_cast<int>(j.x * ti * tilesize),
				static_cast<int>(j.y * ti * tilesize),
				tilesize, tilesize));
			sprite.setPosition(static_cast<float>(x++ * tilesize), static_cast<float>(y * tilesize));
			ret.draw(sprite);
		}
		x = 0;
		y++;
	}
	ret.display();
	map_finished = std::make_unique<sf::Texture>(ret.getTexture());
	auto ret_map = std::make_unique<sf::Sprite>(sf::Sprite(*map_finished.get()));
	ret_map->setPosition(pos.x, pos.y);
	ret.clear();
	return ret_map;
}
void Tilemap::set_map(unsigned _width, unsigned _height, std::vector<std::vector<sf::Vector2f>> &_coords)
{
	data = _coords;
	map_width = _width;
	map_height = _height;
}

bool Tilemap::load_from_file(const std::string &filename)
{
	std::ifstream map(filename);
	std::ifstream mappos(filename + "pos");
	std::ifstream mapsize(filename + "size");
	if (!map.is_open() || !mappos.is_open() || !mapsize.is_open())
	{
		std::cerr << "Error loading map data for \'" << filename << "\'\n";
		return false;
	}
	std::string buff = "";
	mapsize >> buff;
	map_width = std::stoi(buff);
	mapsize >> buff;
	map_height = std::stoi(buff);

	mappos >> buff;
	pos.x = std::stof(buff);
	mappos >> buff;
	pos.y = std::stof(buff);
	buff = "";

	for (unsigned h = 0; h < map_height; h++)
	{
		std::vector<sf::Vector2f> vecbuff;
		for (unsigned w = 0; w < map_width; w++)
		{
			float x, y;
			map >> buff;
			x = std::stof(buff);
			map >> buff;
			y = std::stof(buff);
			vecbuff.push_back(sf::Vector2f(x, y));
		}
		data.push_back(vecbuff);
	}
	return true;
}
void Tilemap::set_position(sf::Vector2f& _pos)
{
	pos = _pos;
}
void Tilemap::set_texture(const sf::Texture texture)
{
	spritesheet = texture;
}
std::unique_ptr<sf::Texture> Tilemap::generate_map()
{
	return std::move(map_finished);
}
void Tilemap::construct_map()
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
std::vector<std::vector<sf::Vector2f>>& Tilemap::get_data() { return data; }