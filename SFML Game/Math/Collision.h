#pragma once
#include <SFML/Graphics.hpp>

class Collision
{
public:
	
	static bool CheckCollision(const sf::RectangleShape& first, const sf::RectangleShape& second);
};

