#include "Application.hpp"

sf::RenderWindow& Application::get_window()
{
	return window;
}
const std::vector<std::unique_ptr<sf::Sprite>>& Application::get_maps()
{
	//Note:
	//	You may be able to use this function to funnel out tilemaps within the windows view, and tilemaps that 
	//	are not by checking their bounds/size and seeing if it's currently within a given (configurable) range.
	return tilemaps;
}
const std::vector<std::unique_ptr<sf::Sprite>>& Application::get_sprites()
{
	// See above note.
	return sprites;
}
const std::vector<std::unique_ptr<sf::Sprite>>& Application::get_players()
{
	return players;
}
const std::vector<std::unique_ptr<AnimatedSprite>>& Application::get_a_sprites()
{
	return a_sprites;
}
const std::vector<std::unique_ptr<sf::Text>>& Application::get_texts()
{
	return texts;
}

const std::vector<std::unique_ptr<CollisionMesh>>& Application::get_collmeshes()
{
	return collisions;
}

const std::vector <std::unique_ptr<DialogBox>>& Application::get_dialogs()
{
	return dialogs;
}