#include "enemyComponent.h"
#include <ECS/entity.h>
#include <ServiceLocator/locator.h>
#include <Physics/ObjectChannels/collisionChannels.h>
#include <Assets/assetManager.h>

#include <GameplayStatics/gameplayStatics.h>
#include <doomlikeGame.h>

#include <Rendering/modelRendererComponent.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>
#include <GameComponents/playerComponent.h>


void EnemyComponent::init()
{
	//  reset the value in case this component was used before (the component manager is a memory pool)
	dead = false;


	//  initialize enemy
	entity = getOwner();

	enemyModel = entity->addComponentByClass<ModelRendererComponent>();
	enemyModel->setModel(&AssetManager::GetModel("enemy"));
	enemyModel->offset.setScale(0.7f);

	collision = entity->addComponentByClass<BoxAABBColComp>();
	collision->setBox(Box{ Vector3::zero, Vector3{0.5f, 0.5f, 0.5f} });
	collision->setCollisionChannel("enemy");
	collision->setCollisionType(CollisionType::Solid);
	collision->onCollisionIntersect.registerObserver(this, Bind_1(&EnemyComponent::onBodyIntersect));

	rigidbody = entity->addComponentByClass<RigidbodyComponent>();
	rigidbody->associateCollision(collision);
	rigidbody->setTestChannels(CollisionChannels::GetRegisteredTestChannel("Enemy"));
	rigidbody->setPhysicsActivated(true);
	rigidbody->setUseGravity(false);

	playerRef = static_cast<DoomlikeGame*>(GameplayStatics::GetGame())->getPlayer().lock();
	if (!playerRef)
	{
		Locator::getLog().LogMessage_Category("Doomlike: An enemy couldn't retrieve the reference of the player!", LogCategory::Warning);
		setUpdateActivated(false);
	}

	entity->addGameplayTag("Enemy");
}

void EnemyComponent::exit()
{
	collision->onCollisionIntersect.unregisterObserver(this);


	//  release shared pointers
	enemyModel = nullptr;
	collision = nullptr;
	rigidbody = nullptr;
	playerRef = nullptr;
}

void EnemyComponent::update(float deltaTime)
{
	rigidbody->setVelocity(Vector3::zero);

	RaycastHitInfos out;
	bool test_player = Locator::getPhysics().LineRaycast(entity->getPosition(), playerRef->getCamPosition(), { "solid", "player" }, out, 0.0f);
	if (!test_player) return;

	if (out.hitDistance > range) return;
	if (!out.hitCollision->getOwner()->hasGameplayTag("Player")) return;

	entity->rotateTowards(playerRef->getCamPosition());

	rigidbody->setVelocity(Vector3::normalize(playerRef->getCamPosition() - entity->getPosition()) * speed);
}

void EnemyComponent::onBodyIntersect(RigidbodyComponent& other)
{
	if (dead) return;

	if (other.getOwner()->hasGameplayTag("Bullet"))
	{
		Locator::getLog().LogMessageToScreen("Doomlike: Enemy die from a bullet.", Color::white, 5.0f);
		dead = true;

		onDie.broadcast(entity);

		//  play death sound
		Locator::getAudio().InstantPlaySound3D(AssetManager::GetSound("enemydeath"), entity->getPosition(), 0.15f);

		entity->destroyEntity();
	}
	else if (other.getOwner()->hasGameplayTag("Player"))
	{
		Locator::getLog().LogMessageToScreen("Doomlike: Player die from the enemy.", Color::white, 5.0f);
		dead = true; //  it allows to avoid this being called twice

		//  play player death sound
		Locator::getAudio().InstantPlaySound2D(AssetManager::GetSound("playerdeath"), 0.4f);

		static_cast<DoomlikeGame*>(GameplayStatics::GetGame())->restartLevel();
	}
}