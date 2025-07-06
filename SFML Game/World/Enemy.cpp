#include "Enemy.h"
#include "../Math/Collision.h"
#include "../World/Player.h" 
#include "../Math/Normalize.h"
#include "Shot.h"


Enemy::Enemy(World& world, std::weak_ptr<Entity> target, sf::Vector2f pos, float speed, const sf::Texture& texture) :
	Entity(world),
	sprite(texture),
	target(target),
	speed(speed)
{


	enemy.setSize(sf::Vector2f(80, 80));
	enemy.setFillColor(sf::Color::Red);
	enemy.setOrigin(sf::Vector2f(enemy.getSize().x / 2, enemy.getSize().y / 2));
	enemy.setPosition(pos);
	sprite.setPosition(enemy.getPosition());


	float scaleX = enemy.getSize().x / sprite.getLocalBounds().size.x;
	float scaleY = enemy.getSize().y / sprite.getLocalBounds().size.y;
	sprite.setScale(sf::Vector2f(scaleX, scaleY));

	sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().size.x / 2, sprite.getLocalBounds().size.y / 2));
	sprite.setPosition(pos);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);

}

void Enemy::Update(float deltaTime)
{

	if (auto t = target.lock()) {
		Player* player = dynamic_cast<Player*>(t.get());
		sf::Vector2f direction = player->getPlayerPos() - enemy.getPosition();

		sf::Vector2f lastPosition = enemy.getPosition();
		enemy.move(normalize(direction) * speed * deltaTime);
		enemy.setRotation(sf::degrees(std::atan2(direction.y, direction.x) * 180.f / 3.14 - 90.f));
		sprite.setPosition(enemy.getPosition());
		sprite.setRotation(enemy.getRotation());

	}
	else {
		target = world.GetPlayer();
	}
}

bool Enemy::IsCollideWith(const Entity& other) const {

	return Collision::CheckCollision(this->GetRectangleShape(), other.GetRectangleShape());


}

const sf::RectangleShape& Enemy::GetRectangleShape() const
{
	return enemy;
}

void Enemy::OnCollision(Entity& other)
{
	if (dynamic_cast<Shot*>(&other) != nullptr)
	{
		OnDestroy();
	}
	else if (auto a = dynamic_cast<Enemy*>(&other))
	{
		sf::Vector2f delta = this->enemy.getPosition() - a->GetRectangleShape().getPosition();
		float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
		if (distance == 0) return; // щоб уникнути ділення на нуль


		sf::Vector2f direction = normalize(delta);


		float pushDistance = 1.0f;

		this->enemy.move(direction * pushDistance);

	}

}
