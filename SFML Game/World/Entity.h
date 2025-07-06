#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "World.h"
class Entity : public sf::Drawable
{
public:

	sf::Vector2f pos;

	World& world;
	bool isEnable = true;

	Entity(World& world);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Update(float deltaTime) = 0;
	virtual bool IsCollideWith(const Entity& other) const = 0;
	virtual const sf::RectangleShape& GetRectangleShape() const = 0;

	virtual void OnCollision(Entity& other) = 0;
	virtual void OnDestroy();
};

