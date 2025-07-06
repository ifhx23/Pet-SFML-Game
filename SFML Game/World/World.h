#pragma once
#include <SFML/Graphics.hpp>

class Entity;

class World : public sf::Drawable 
{
public:
	World();

	~World();
	void AddEntity(std::shared_ptr<Entity>  entity);
	void Render();
	void Update(float deltaTime);
	int GetEnemyCount() const;
	std::shared_ptr<Entity> GetPlayer() const;
	bool IsEntityCollideWithOthers(std::shared_ptr<Entity> e) const;
	void ResetWorld();
private:
	std::list<std::shared_ptr<Entity>> entities;
	virtual void draw( sf::RenderTarget& target, sf::RenderStates states) const override;

	void AllCollidedEntities() const;

	void EraseAllDeadEntities();
	
	
};

