#include "TextureManager.hpp"

#include <iostream>

TextureManager::TextureManager()
{
	missing_texture = generate_missing_texture();
}

bool TextureManager::load(TextureID id, const std::string &filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename))
		return false;
	else
		textures.insert(std::make_pair(id, std::move(texture)));
	return true;
}

const sf::Texture& TextureManager::get(TextureID id)
{
	auto found = textures.find(id);
	if (found == textures.end())
	{
		std::cerr << "Error: could not find texture id " << texture_names[id] << ". Textures may be missing.\n";
		//std::exit(-1);
		return missing_texture;
	}
	else
	{
		return *found->second;
	}
}

// TODO: Figure out why get(id) fails, then use this function.
const sf::Texture TextureManager::generate_missing_texture()
{
	sf::RenderTexture ret;
	
	ret.create(16, 16);
	
	sf::RectangleShape square;
	
	// First Square (Magenta)
	square.setFillColor(sf::Color::Magenta);
	square.setSize({8.f, 8.f});
	square.setPosition({ 0, 0 });
	ret.draw(square);

	// Fourth Square (Magenta)
	square.setPosition({ 9, 9 });
	ret.draw(square);

	// Second Square (Cyan)
	square.setFillColor(sf::Color::Cyan);
	square.setPosition({ 9, 0 });
	ret.draw(square);

	// Third Square (Cyan)
	square.setPosition({ 0, 9 });
	ret.draw(square);

	// Get the generated texture
	ret.display();
	return ret.getTexture();
}


TextureManager::~TextureManager()
{
}
