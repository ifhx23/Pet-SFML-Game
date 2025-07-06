#pragma once
#include "Entity.h"

class Enemy :
	public Entity
{
public:
	Enemy(World& world, std::weak_ptr<Entity> target,sf::Vector2f pos, float speed, const sf::Texture& texture);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Update(float deltaTime);
	virtual bool IsCollideWith(const Entity& other) const;
	virtual const sf::RectangleShape& GetRectangleShape() const override;
	virtual void OnCollision(Entity& other) override;
private:
	sf::RectangleShape enemy;
	sf::Sprite sprite; // Sprite for the enemy
	float speed = 100.0f; // Speed of the enemy
	sf::Vector2f moveDirection; // Direction in which the enemy moves
	std::weak_ptr<Entity> target; // Pointer to the player entity for collision detection
};

