#include "enemyCount.h"
#include <ServiceLocator/locator.h>

#include <ECS/entity.h>
#include <GameComponents/enemyComponent.h>
#include <algorithm>


void EnemyCount::addEnemy(Entity* enemyToAdd)
{
	std::shared_ptr<EnemyComponent> enemy_comp = enemyToAdd->getComponentByClass<EnemyComponent>();

	if (!enemy_comp)
	{
		Locator::getLog().LogMessage_Category("Doomlike: Tried to add an entity to an Enemy Count that doesn't have the Enemy Component!", LogCategory::Warning);
		return;
	}

	enemies.push_back(enemyToAdd);
	enemy_comp->onDie.registerObserver(this, Bind_1(&EnemyCount::onEnemyDie));
}

void EnemyCount::addEnemies(std::vector<Entity*> enemiesToAdd)
{
	for (auto enemy : enemiesToAdd)
		addEnemy(enemy);
}

void EnemyCount::clearEnemyCount(bool clearEvent)
{
	enemies.clear();
	if (clearEvent) onAllEnemiesDead.clearAllObservers();
}

void EnemyCount::onEnemyDie(Entity* enemyDead)
{
	auto iter = std::find(enemies.begin(), enemies.end(), enemyDead);
	if (iter != enemies.end())
	{
		std::iter_swap(iter, enemies.end() - 1);
		enemies.pop_back();
	}

	if (enemies.size() == 0)
	{
		onAllEnemiesDead.broadcast();
	}
}