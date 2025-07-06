#include "Collision.h"

bool Collision::CheckCollision(const sf::RectangleShape& first,const sf::RectangleShape& second)
{
	
    return first.getGlobalBounds().findIntersection(second.getGlobalBounds()).has_value();
}
