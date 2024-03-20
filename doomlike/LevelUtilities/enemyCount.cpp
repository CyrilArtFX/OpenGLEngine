#include "enemyCount.h"

#include <algorithm>


void EnemyCount::addEnemy(Enemy* enemyToAdd)
{
	enemies.push_back(enemyToAdd);
	enemyToAdd->onDie.registerObserver(this, Bind_1(&EnemyCount::onEnemyDie));
}

void EnemyCount::addEnemies(std::vector<Enemy*> enemiesToAdd)
{
	for (auto enemy : enemiesToAdd)
		addEnemy(enemy);
}

void EnemyCount::clearEnemies(bool clearEvent)
{
	enemies.clear();
	if (clearEvent) onAllEnemiesDead.clearAllObservers();
}

void EnemyCount::onEnemyDie(Enemy* enemyDead)
{
	auto iter = std::find(enemies.begin(), enemies.end(), enemyDead);
	if (iter != enemies.end())
	{
		std::iter_swap(iter, enemies.end() - 1);
		enemies.pop_back();
	}

	if (enemies.size() == 0)
	{
		enemiesAllDead();
	}
}

void EnemyCount::enemiesAllDead()
{
	onAllEnemiesDead.broadcast();
}
