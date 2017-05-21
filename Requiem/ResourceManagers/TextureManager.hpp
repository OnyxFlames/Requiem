#pragma once

#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "../Debug_Utils.hpp"


/****
*	TextureManager class.
*	Stores every instance of a texture loaded with an enum ID tied to it.
*	This is so that different objects have access to already loaded textures and there aren't multiple copies of textures loaded at a time.
****/

static const char* texture_names[]
{
	"MissingTexture",
	"TextureID::Player",
	"TextureID::Characters",
	"TextureID::City",
	"Texture::ID::Cave",
};

enum TextureID
{
	MissingNo = 0,	// heh
	Player,
	Characters,
	City,
	Cave,
};

class TextureManager
{
private:
	sf::Texture missing_texture;
	std::map<TextureID, std::unique_ptr<sf::Texture>> textures;
	const sf::Texture generate_missing_texture();
public:
	TextureManager();
	// Bind a texture to an id and store it in the map
	bool load(TextureID id, const std::string &filename);
	const sf::Texture& get(TextureID id);
	~TextureManager();
};

