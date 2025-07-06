
#include "Shot.h"
#include "Player.h"
#include "../Math/Collision.h"
Shot::Shot(World& world, float moveSpeed) :Entity(world)
{
	this->moveSpeed = moveSpeed;

}


PlayerShot::PlayerShot(Player& whoShoots) :Shot(whoShoots.world, 1000.f)
{
	duration = 5.0f;
	shot.setSize(sf::Vector2f(10, 10));
	shot.setFillColor(sf::Color::White);
	shot.setOrigin(sf::Vector2f(shot.getSize().x / 2, shot.getSize().y / 2));
	shot.setPosition({ whoShoots.getPlayerPos() });
	shot.setRotation(sf::degrees(whoShoots.GetPlayerTower() - 90.f));
}
void PlayerShot::Update(float deltaTime)
{
	duration -= deltaTime;
	if (duration < 0)
		isEnable = false;

	shot.move(sf::Vector2f(std::cos(shot.getRotation().asRadians()), std::sin(shot.getRotation().asRadians())) * moveSpeed * deltaTime);
}



void PlayerShot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shot);
}
const sf::RectangleShape& PlayerShot::GetRectangleShape() const 
{
	return shot;
}

void PlayerShot::OnCollision(Entity& other)
{
	if (dynamic_cast<Player*>(&other) == nullptr) {
		isEnable = false;
	}
	
}

bool PlayerShot::IsCollideWith(const Entity& other)const {
	if (dynamic_cast<const Player*>(&other) == nullptr)

		return Collision::CheckCollision(this->GetRectangleShape(), other.GetRectangleShape());

	else
		return false;
}


