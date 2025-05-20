#include "doomlikeLevelStart.h"
#include <ServiceLocator/locator.h>
#include <Assets/assetManager.h>
#include <GameplayStatics/gameplayStatics.h>
#include <doomlikeGame.h>

#include <Rendering/Lights/directionalLightComponent.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>
#include <GameComponents/enemyComponent.h>

#include <PrefabFactories/wallFactory.h>
#include <PrefabFactories/floorCeilingFactory.h>
#include <PrefabFactories/stairFactory.h>
#include <PrefabFactories/lampFactory.h>

using WallFactory::WallFacingDirection;


void DoomlikeLevelStart::loadScene()
{
	Renderer& renderer = Locator::getRenderer();
	renderer.SetClearColor(Color{ 50, 75, 75, 255 });


	//  prefabs
	FloorCeilingFactory::CreateFloor(this, Vector3{ 0.0f, 0.0f,  2.5f }, Vector2{  5.0f, 10.0f }, true);
	FloorCeilingFactory::CreateFloor(this, Vector3{ 0.0f, 0.0f, 15.0f }, Vector2{ 15.0f, 15.0f }, true);
	FloorCeilingFactory::CreateCeiling(this, Vector3{ 0.0f, 3.0f,  2.5f }, Vector2{  5.0f, 10.0f });
	FloorCeilingFactory::CreateCeiling(this, Vector3{ 0.0f, 5.0f, 15.0f }, Vector2{ 15.0f, 15.0f });

	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveZ, Vector3{  0.0f, 1.5f, -2.5f }, Vector2{  5.0f, 3.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveX, Vector3{ -2.5f, 1.5f,  2.5f }, Vector2{ 10.0f, 3.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeX, Vector3{  2.5f, 1.5f,  2.5f }, Vector2{ 10.0f, 3.0f }, false);

	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveZ, Vector3{ -5.0f, 2.5f,   7.5f }, Vector2{  5.0f, 5.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveZ, Vector3{  0.0f, 4.0f,   7.5f }, Vector2{  5.0f, 2.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveZ, Vector3{  5.0f, 2.5f,   7.5f }, Vector2{  5.0f, 5.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeX, Vector3{  7.5f, 2.5f,  15.0f }, Vector2{ 15.0f, 5.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeZ, Vector3{ -5.0f, 2.5f,  22.5f }, Vector2{ 25.0f, 5.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveX, Vector3{ -7.5f, 2.5f, 12.25f }, Vector2{  9.5f, 5.0f }, false);

	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeZ, Vector3{  -2.5f, 2.5f, 11.75f }, Vector2{ 1.5f, 5.0f }, true);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveX, Vector3{ -1.75f, 2.5f,  12.5f }, Vector2{ 1.5f, 5.0f }, true);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeX, Vector3{ -3.25f, 2.5f,  12.5f }, Vector2{ 1.5f, 5.0f }, true);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveZ, Vector3{  -2.5f, 2.5f, 13.25f }, Vector2{ 1.5f, 5.0f }, true);

	StairFactory::CreateStair(this, StairFactory::StairFacingDirection::StairFacingNegativeZ, Vector3{ 3.8f, 0.0f, 16.0f });
	FloorCeilingFactory::CreateFloor(this, Vector3{ -5.0f, 2.0f, 19.75f }, Vector2{ 25.0f, 5.5f }, true);
	FloorCeilingFactory::CreateCeiling(this, Vector3{ -12.5f, 5.0f, 19.75f }, Vector2{ 10.0f, 5.5f });
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeZ, Vector3{   0.0f, 1.0f, 17.0f }, Vector2{ 15.0f, 2.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveZ, Vector3{ -12.5f, 3.5f, 17.0f }, Vector2{ 10.0f, 3.0f }, false);

	endLevelWall = WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveX, Vector3{ -7.5f, 3.5f, 19.75f }, Vector2{ 5.5f, 3.0f }, false);

	LampFactory::CreateLamp(this, Vector3{ -3.2f, 0.0f,  8.3f }, 2.3f, false);
	LampFactory::CreateLamp(this, Vector3{  3.2f, 0.0f,  8.3f }, 2.3f, false);
	LampFactory::CreateLamp(this, Vector3{  6.5f, 2.0f, 21.5f }, 2.3f, false);
	LampFactory::CreateLamp(this, Vector3{ -3.0f, 5.0f, 16.5f }, 1.7f, true);

	//  directional light
	Entity* light = createEntity();
	std::shared_ptr<DirectionalLightComponent> dir_light_comp = light->addComponentByClass<DirectionalLightComponent>();
	dir_light_comp->setColor(Color{ 255, 238, 209, 255 });
	dir_light_comp->setDirection(Vector3::unitY);
	dir_light_comp->setAmbientStrength(0.35f);
	dir_light_comp->setDiffuseStrength(0.0f);


	//  enemies
	/*Entity* enemy_1 = createEntity();
	Entity* enemy_2 = createEntity();
	enemy_1->setPosition(Vector3{ 3.5f, 1.2f,  11.5f });
	enemy_2->setPosition(Vector3{ -3.5f, 3.2f, 20.0f });
	enemy_1->addComponentByClass<EnemyComponent>();
	enemy_2->addComponentByClass<EnemyComponent>();

	enemyCount.addEnemies({ enemy_1, enemy_2 });
	enemyCount.onAllEnemiesDead.registerObserver(this, Bind_0(&DoomlikeLevelStart::onEnemiesDead));*/


	//  trigger zone
	endLevelZone = createEntity();
	endLevelZone->setPosition(Vector3{ -15.0f, 3.5f, 19.75f });
	endLevelZone->setScale(Vector3{ 4.0f, 2.5f, 4.8f });
	std::shared_ptr<BoxAABBColComp> trigger_comp = endLevelZone->addComponentByClass<BoxAABBColComp>();
	trigger_comp->setBox(Box::one);
	trigger_comp->setCollisionChannel("trigger_zone");
	trigger_comp->setCollisionType(CollisionType::Trigger);
	trigger_comp->onTriggerEnter.registerObserver(this, Bind_1(&DoomlikeLevelStart::onEnterEndLevelZone));


	//  player spawn point
	spawnPoint = createEntity();
	spawnPoint->setPosition(Vector3::zero);
	spawnPoint->setRotation(Quaternion::fromEuler(Maths::toRadians(-90.0f), 0.0f, 0.0f));
}

void DoomlikeLevelStart::unloadScene()
{
	enemyCount.clearEnemyCount(true);
}

void DoomlikeLevelStart::updateScene(float dt)
{
}

void DoomlikeLevelStart::onEnemiesDead()
{
	Locator::getLog().LogMessageToScreen("Doomlike Intro Level: All enemies of the level are dead!", Color::white, 5.0f);
	endLevelWall->setPosition(Vector3{ -17.5f, 3.5f, 19.75f });
}

void DoomlikeLevelStart::onEnterEndLevelZone(RigidbodyComponent& other)
{
	if (!other.getOwner()->hasGameplayTag("Player")) return;

	Locator::getLog().LogMessageToScreen("Doomlike Intro Level: Player exit intro level.", Color::white, 5.0f);
	static_cast<DoomlikeGame*>(GameplayStatics::GetGame())->changeLevel(3);

	endLevelZone->getComponentByClass<BoxAABBColComp>()->onTriggerEnter.unregisterObserver(this);
}