#include "World.h"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
World::World()
{

}

World::~World()
{

}
void World::Update(float deltaTime) {
	AllCollidedEntities();
	EraseAllDeadEntities();

	for (auto& entity : entities) {
		if (entity.get()->isEnable)
		{
			entity->Update(deltaTime);
		}

	}
}




int World::GetEnemyCount() const
{
	int enemyCount = 0;
	for (const auto& entity : entities) {
		if (dynamic_cast<Enemy*>(entity.get())) {
			enemyCount++;
		}
	}
	return enemyCount;
}
std::shared_ptr<Entity> World::GetPlayer() const
{
	for (const auto& entity : entities)
	{
		if (dynamic_cast<Player*>(entity.get()))
		{
			return entity;
		}
	}
}
void World::AddEntity(std::shared_ptr<Entity> entity)
{
	entities.push_back(std::move(entity));
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& entity : entities) {
		target.draw(*entity, states);
	}
}
void World::AllCollidedEntities() const
{
	for (auto outerIterator = entities.cbegin(), end = entities.cend(); outerIterator != end; ++outerIterator)
	{
		Entity& entity1 = **outerIterator;
		auto innterIterator = outerIterator;
		++innterIterator;

		for (; innterIterator != end; ++innterIterator)
		{
			Entity& entity2 = **innterIterator;

			/*if (entity1.isEnable && entity1.IsCollideWith(entity2))
				entity1.OnDestroy();


			if (entity2.isEnable && entity2.IsCollideWith(entity1))
				entity2.OnDestroy();
					*/
			if (entity1.isEnable && entity2.isEnable && entity1.IsCollideWith(entity2)) {
				entity1.OnCollision(entity2);
				entity2.OnCollision(entity1);
			}
		}
	}
}

void World::EraseAllDeadEntities()
{
	for (auto entityIterator = entities.begin(); entityIterator != entities.end();)
	{
		if (!(*entityIterator)->isEnable)
		{
			entityIterator->reset();
			entityIterator = entities.erase(entityIterator);
		}
		else
		{
			++entityIterator;
		}
	}

}
bool World::IsEntityCollideWithOthers(std::shared_ptr<Entity> e) const
{
	for (const auto& other : entities)
		if (other.get()->IsCollideWith(*e.get()))
			return true;

	return false;
}

void World::ResetWorld()
{
	entities.clear();
}

