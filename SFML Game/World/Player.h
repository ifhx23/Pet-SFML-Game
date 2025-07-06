#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "../Input/InputManeger.h"
#include <math.h>

class Player :
	public Entity
{
public:
	
	
	
	Player(InputManeger& input, World& world, sf::Texture& head, sf::Texture& body);
	virtual void Update(float deltatime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f getPlayerPos();
	void Shoot();
	float getRotationToCursor(const sf::Vector2f& playerPos, const sf::Vector2f& mousePos);
	virtual bool IsCollideWith(const Entity& other) const;
	float GetPlayerRotate();
	float GetPlayerTower();
	virtual const sf::RectangleShape& GetRectangleShape() const;
	virtual void OnDestroy() override;
	int GetLives() const { return lives; }
	void Hit();
	virtual void OnCollision(Entity& other) override;

private:
	InputManeger* input;
	sf::RectangleShape player;
	int lives = 3;
	float timeSinceLastShoot=0.f;
	float timeLatsHit = 1.f;
	float speed = 300.0f;
	sf::Vector2f directionMove;
	sf::Sprite head;
	sf::Sprite body;
};

