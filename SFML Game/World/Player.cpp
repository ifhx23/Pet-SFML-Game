#include "Player.h"
#include "../Math/Normalize.h"
#define M_PI 3.14159265358979323846
#include "Shot.h"
#include "../Math/Collision.h"
#include "Enemy.h"
#include <iostream>

Player::Player(InputManeger& input, World& world,sf::Texture& head, sf::Texture& body) : 
	Entity(world),
	head(head),
	body(body)
{
	this->input = &input;

	player.setSize(sf::Vector2f(50, 70));
	player.setFillColor(sf::Color::Green);
	player.setOrigin(sf::Vector2f(player.getSize().x / 2, player.getSize().y / 2));
	player.setPosition({ 500, 500 });

	float scaleX = player.getSize().x / this->body.getLocalBounds().size.x;
	float scaleY = player.getSize().y / this->body.getLocalBounds().size.y;
	this->body.setScale(sf::Vector2f(scaleX, scaleY));

	this->body.setOrigin(sf::Vector2f(this->body.getLocalBounds().size.x / 2, this->body.getLocalBounds().size.y / 2));
	this->body.setPosition(pos);

	this->head.setScale(sf::Vector2f(scaleX, scaleY));
	this->head.setOrigin(sf::Vector2f(this->head.getLocalBounds().size.x / 2, this->head.getLocalBounds().size.y / 2));
	this->head.setPosition(pos);
}

void Player::Update(float deltaTime)
{
	Player::timeSinceLastShoot += deltaTime;
	Player::timeLatsHit += deltaTime;
	if (timeLatsHit<1.f)
	{
		head.setColor(sf::Color::Red);
		body.setColor(sf::Color::Red);
	}
	else {
		head.setColor(sf::Color::White);
		body.setColor(sf::Color::White);
	}
	directionMove = {};
	if (input->isKeyHeld(PlayerAction::MoveUp))    directionMove.y -= 1.f;
	if (input->isKeyHeld(PlayerAction::MoveDown))  directionMove.y += 1.f;
	if (input->isKeyHeld(PlayerAction::MoveLeft))  directionMove.x -= 1.f;
	if (input->isKeyHeld(PlayerAction::MoveRight)) directionMove.x += 1.f;
	if (input->isKeyHeld(PlayerAction::Shot)) Shoot();

	//player.setRotation(sf::degrees(getRotationToCursor(input->mousePosition, getPlayerPos()) + 90.f));

	player.move(normalize(directionMove) * speed * deltaTime);
	body.setPosition(player.getPosition());
	if (directionMove.x != 0.f || directionMove.y != 0.f) {
		float moveAngle = std::atan2(directionMove.y, directionMove.x) * 180.f / M_PI;
		player.setRotation(sf::degrees(moveAngle + 90.f));
		body.setRotation(sf::degrees(moveAngle + 90.f));
	}
	head.setPosition(player.getPosition());
	head.setOrigin({ 102.f,258.f });
	head.setRotation(sf::degrees(this->getRotationToCursor(input->mousePosition, getPlayerPos())-90));
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(body);
	target.draw(head);
}

sf::Vector2f Player::getPlayerPos()
{
	return player.getPosition();
}

void Player::Shoot()
{
	if (timeSinceLastShoot > 0.5f)
	{
		world.AddEntity(std::make_unique<PlayerShot>(*this));
		timeSinceLastShoot = 0;
	}
}

float Player::getRotationToCursor(const sf::Vector2f& playerPos, const sf::Vector2f& mousePos)
{
	sf::Vector2f direction = mousePos - playerPos;
	return std::atan2(direction.y, direction.x) * 180.f / M_PI;
}

bool Player::IsCollideWith(const Entity& other) const
{
	return Collision::CheckCollision(this->GetRectangleShape(), other.GetRectangleShape());
}

float Player::GetPlayerRotate()
{
	return player.getRotation().asDegrees();

}
float Player::GetPlayerTower()
{
	return head.getRotation().asDegrees();

}

const sf::RectangleShape& Player::GetRectangleShape() const
{
	return player;
}

void Player::OnDestroy()
{

	//Entity::OnDestroy();


}

void Player::Hit()
{
	if (timeLatsHit > 1.f) {
		std::cout << "Player hit!" << std::endl;
		lives--;
		timeLatsHit = 0.f;
	}
}

void Player::OnCollision(Entity& other)
{
	if (dynamic_cast<Enemy*>(&other))
	{
		Hit();	
	}
}



