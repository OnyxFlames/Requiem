#include "Entity.hpp"

Entity::Entity(const sf::Texture &texture)
{
	entity.setTexture(texture);
	entity.setTextureRect({ 0, 0, 128, 128 });
}
Entity::~Entity()
{ }
void Entity::set_velocity(sf::Vector2f _vel)
{
	velocity = _vel;
}
void Entity::update(const sf::Time &delta)
{
	entity.move(sf::Vector2f(velocity.x * delta.asMicroseconds(), velocity.y * delta.asMicroseconds()));

	if (velocity.x > 0)
		velocity.x -= drag;
	else if (velocity.x < 0)
		velocity.x += drag;

	if (velocity.y > 0)
		velocity.y -= drag;
	else if (velocity.y < 0)
		velocity.y += drag;

	if (velocity.x < 0.02f && velocity.x > -0.02f)
		velocity.x = 0;
	if (velocity.y < 0.02f && velocity.y > -0.02f)
		velocity.y = 0;
}
sf::Sprite& Entity::get() { return entity; }