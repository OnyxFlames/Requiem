#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Debug_Utils.hpp"

class CollisionMesh
{
private:
	std::vector<sf::IntRect> collisions;
public:
	CollisionMesh();
	~CollisionMesh();

	void load_from_file(const std::string &filename);

	std::vector<sf::IntRect>& get_collmesh();
};

