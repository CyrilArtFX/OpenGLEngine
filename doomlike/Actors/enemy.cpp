#include "enemy.h"
#include <ServiceLocator/locator.h>
#include <ServiceLocator/physics.h>
#include <ServiceLocator/audio.h>
#include <Physics/ObjectChannels/collisionChannels.h>
#include <Assets/assetManager.h>

#include "Player.h"
#include <doomlikeGame.h>
#include <GameplayStatics/gameplayStatics.h>

#include <iostream>


void Enemy::load()
{
	Physics& physics = Locator::getPhysics();

	addModel(&AssetManager::GetModel("enemy"));

	rigidbody = &physics.CreateRigidbodyComponent(new RigidbodyComponent(new BoxAABBColComp(Box{Vector3::zero, Vector3{0.7f, 0.7f, 0.7f}}, this, false, "enemy"), true));
	rigidbody->getAssociatedCollisionNonConst().onCollisionIntersect.registerObserver(this, Bind_1(&Enemy::onBodyIntersect));
	rigidbody->setTestChannels(CollisionChannels::GetRegisteredTestChannel("Enemy"));

	rigidbody->setUseGravity(false);

	setScale(0.7f);

	playerRef = static_cast<DoomlikeGame*>(GameplayStatics::GetGame())->getPlayer();
}

void Enemy::updateObject(float dt)
{
	if (dead)
	{
		onDie.broadcast(this);
		delete rigidbody;
		GameplayStatics::GetActiveScene()->unregisterObject(this);
		return;
	}

	rigidbody->setVelocity(Vector3::zero);

	if (!playerRef) return;

	RaycastHitInfos out;
	bool test_player = Locator::getPhysics().LineRaycast(getPosition(), playerRef->getEyePosition(), { "solid", "player" }, out, 0.0f);
	if (!test_player) return;

	if (out.hitDistance > range) return;

	if (out.hitCollision->getCollisionChannel() != "player") return;

	rotateTowards(playerRef->getPosition());
	rigidbody->setVelocity(Vector3::normalize(playerRef->getEyePosition() - getPosition()) * speed);
}

void Enemy::onBodyIntersect(RigidbodyComponent& other)
{
	if (other.getAssociatedCollision().getCollisionChannel() == "bullet")
	{
		std::cout << "Enemy die from a bullet.\n";
		dead = true;
		//  not safe to delete rigidbody here cause it's during the update physics step
		//  might need a way to automate this with a pending system


		//  play death sound
		Locator::getAudio().InstantPlaySound3D(AssetManager::GetSound("enemydeath"), getPosition(), 0.15f);
	}
	else if (other.getAssociatedCollision().getCollisionChannel() == "player")
	{
		std::cout << "Player die from the enemy.\n";
		static_cast<DoomlikeGame*>(GameplayStatics::GetGame())->restartLevel();

		//  play player death sound
		Locator::getAudio().InstantPlaySound2D(AssetManager::GetSound("playerdeath"), 0.4f);
	}
}