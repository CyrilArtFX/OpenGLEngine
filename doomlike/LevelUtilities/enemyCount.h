#pragma once
#include <Actors/enemy.h>

#include <Events/event.h>
#include <Events/observer.h>

#include <vector>


class EnemyCount : public Observer
{
public:
	EnemyCount() {}

	void addEnemy(Enemy* enemyToAdd);
	void addEnemies(std::vector<Enemy*> enemiesToAdd);

	void clearEnemies(bool clearEvent);

	Event<> onAllEnemiesDead;

private:
	std::vector<Enemy*> enemies;


	void onEnemyDie(Enemy* enemyDead);
	void enemiesAllDead();
};

