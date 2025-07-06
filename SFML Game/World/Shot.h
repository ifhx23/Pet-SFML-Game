#pragma once
#include "Entity.h"

class Player;
class World;
class Shot :public Entity
{
public:
	Shot(World& world, float moveSpeed);
	virtual void OnCollision(Entity& other) = 0;
	virtual void Update(float deltaTime) = 0;
	//virtual sf::RectangleShape& GetRectangleShape() const = 0;
protected:
	float duration = 0;
public:
	float moveSpeed;
};

class PlayerShot : public Shot
{
public:
	PlayerShot(Player& whoShoots);
	virtual void Update(float deltaTime);
	virtual bool IsCollideWith(const Entity& other) const override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual const sf::RectangleShape& GetRectangleShape() const  override;
	virtual void OnCollision(Entity& other) override;
private:
	sf::RectangleShape shot;
};


