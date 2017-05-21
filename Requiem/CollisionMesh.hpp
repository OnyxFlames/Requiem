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

	void load_from_file(const std::string &filename)
	{
		std::ifstream coll(filename);
		if (!coll.is_open())
		{
			std::cerr << "Error loading mesh data for " << filename << "\n";
			return;
		}
		std::string buff;
		short lines = 0;
		while (std::getline(coll, buff))
		{
			lines++;
		}
		coll.close();
		coll.open(filename);

		for (int i = 0; i < lines; i++)
		{
			int left = 0, top = 0, width = 0, height = 0;
			sf::IntRect temp;
			//buff = "";
			coll >> buff;
			left = std::stoi(buff);
			temp.left = left;
			
			coll >> buff;
			top = std::stoi(buff);
			temp.top = top;

			coll >> buff;
			width = std::stoi(buff);
			temp.width = width;

			coll >> buff;
			height = std::stoi(buff);
			temp.height = height;

			collisions.push_back(std::move(temp));
#ifdef DEBUG
			//std::cout << "Added into mesh: left: " << temp.left << " top: " << temp.top << " width: " << temp.width << " height: " << temp.height << "\n";
#endif
		}

	}
	std::vector<sf::IntRect>& get_collmesh()
	{
		return collisions;
	}
};

