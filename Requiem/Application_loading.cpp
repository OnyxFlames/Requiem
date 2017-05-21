#include "Application.hpp"

void Application::add_tilemap(std::unique_ptr<sf::Sprite> _tilemap)
{
	tilemaps.push_back(std::move(_tilemap));
}
void Application::add_player(std::unique_ptr<sf::Sprite> _player)
{
	players.push_back(std::move(_player));
}
void Application::add_a_sprite(std::unique_ptr<AnimatedSprite> _a_sprite)
{
	a_sprites.push_back(std::move(_a_sprite));
}
void Application::add_collisionmesh(std::unique_ptr<CollisionMesh> coll_mesh)
{
	collisions.push_back(std::move(coll_mesh));
}
void Application::add_dialog(std::unique_ptr<DialogBox> dialog_box)
{
	dialogs.push_back(std::move(dialog_box));
}