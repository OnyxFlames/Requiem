#pragma once

#include <SFML/Graphics.hpp>



class Entity
{
private:
	const float drag = 0.01f;
	sf::Sprite entity;
	sf::Vector2f velocity = { 0.f, 0.f };
public:
	Entity(const sf::Texture &texture);
	void set_velocity(sf::Vector2f _vel);
	void update(const sf::Time &delta);
	sf::Sprite& get();
	~Entity();
};

