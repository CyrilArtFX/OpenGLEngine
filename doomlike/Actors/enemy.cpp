#include "enemy.h"
#include <Physics/physics.h>
#include <Assets/assetManager.h>

#include "Player.h"
#include <doomlikeGame.h>
#include <GameplayStatics/gameplayStatics.h>

#include <iostream>


void Enemy::load()
{
	addModel(&AssetManager::GetModel("enemy"));

	rigidbody = &Physics::CreateRigidbodyComponent(new RigidbodyComponent(new BoxAABBColComp(Box{Vector3::zero, Vector3{0.7f, 0.7f, 0.7f}}, this, false, "enemy"), false, true));
	rigidbody->getAssociatedCollisionNonConst().onCollisionIntersect.registerObserver(this, Bind_1(&Enemy::onBodyIntersect));

	rigidbody->setUseGravity(false);

	setScale(0.7f);

	playerRef = static_cast<DoomlikeGame*>(GameplayStatics::GetGame())->getPlayer();
}

void Enemy::update(float dt)
{
	if (!playerRef) return;

	RaycastHitInfos out;
	bool test_player = Physics::LineRaycast(getPosition(), playerRef->getEyePosition(), { "solid", "player" }, out, 0.0f);
	if (!test_player) return;

	const Player* player_visibility = dynamic_cast<const Player*>(out.hitCollision->getAssociatedObject());
	if (!player_visibility) return;

	//  TODO: find a way to make a good look at rotation for enemy
	//rotateTowards(player_visibility->getEyePosition());
}

void Enemy::onBodyIntersect(RigidbodyComponent& other)
{
	if (other.getAssociatedCollision().getCollisionChannel() == "bullet")
	{
		//  TODO: implement proper object destruction with correct unregister for renderer
		std::cout << "Enemy Die\n";
	}
}