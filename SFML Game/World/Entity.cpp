#include "Entity.h"

Entity::Entity(World& world):world(world)
{
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void Entity::OnDestroy()
{
	this->isEnable = false;
}
