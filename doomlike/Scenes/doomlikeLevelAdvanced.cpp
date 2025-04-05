#include "doomlikeLevelAdvanced.h"
#include <ServiceLocator/locator.h>
#include <Assets/assetManager.h>

#include <Rendering/Lights/directionalLightComponent.h>
#include <GameComponents/lampComponent.h>

#include <PrefabFactories/wallFactory.h>
#include <PrefabFactories/floorCeilingFactory.h>
#include <PrefabFactories/lampFactory.h>

//#include <Actors/movingPlatform.h>
//#include <LevelUtilities/triggerZone.h>

using WallFactory::WallFacingDirection;


void DoomlikeLevelAdvanced::loadScene()
{
	Renderer& renderer = Locator::getRenderer();
	renderer.SetClearColor(Color{ 50, 75, 75, 255 });


	//  prefabs - static
	FloorCeilingFactory::CreateFloor(this, Vector3{ 0.0f, 0.0f, 0.0f }, Vector2{ 20.0f, 20.0f }, false);
	FloorCeilingFactory::CreateFloor(this, Vector3{ 0.0f, 7.0f, 0.0f }, Vector2{  2.5f,  2.5f }, true);
	FloorCeilingFactory::CreateCeiling(this, Vector3{ 0.0f, 10.0f, 0.0f }, Vector2{ 20.0f, 20.0f });

	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeZ, Vector3{   0.0f, 3.5f, -1.25f }, Vector2{ 2.5f, 7.0f });
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveX, Vector3{  1.25f, 3.5f,   0.0f }, Vector2{ 2.5f, 7.0f });
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeX, Vector3{ -1.25f, 3.5f,   0.0f }, Vector2{ 2.5f, 7.0f });
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveZ, Vector3{   0.0f, 3.5f,  1.25f }, Vector2{ 2.5f, 7.0f });

	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeZ, Vector3{   0.0f, 5.0f,  10.0f }, Vector2{ 20.0f, 10.0f });
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveX, Vector3{ -10.0f, 5.0f,   0.0f }, Vector2{ 20.0f, 10.0f });
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeX, Vector3{  10.0f, 5.0f,   0.0f }, Vector2{ 20.0f, 10.0f });
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveZ, Vector3{   0.0f, 5.0f, -10.0f }, Vector2{ 20.0f, 10.0f });

	//  prefabs - dynamic
	ceilLamp1 = LampFactory::CreateLamp(this, Vector3{ -8.0f, 10.0f, -8.0f }, true, true);
	ceilLamp2 = LampFactory::CreateLamp(this, Vector3{  8.0f, 10.0f, -8.0f }, true, true);
	ceilLamp3 = LampFactory::CreateLamp(this, Vector3{ -8.0f, 10.0f,  8.0f }, true, true);
	ceilLamp4 = LampFactory::CreateLamp(this, Vector3{  8.0f, 10.0f,  8.0f }, true, true);
	ceilLamp5 = LampFactory::CreateLamp(this, Vector3{ -8.0f, 10.0f,  0.0f }, true, true);
	ceilLamp6 = LampFactory::CreateLamp(this, Vector3{  8.0f, 10.0f,  0.0f }, true, true);
	ceilLamp7 = LampFactory::CreateLamp(this, Vector3{  0.0f, 10.0f, -8.0f }, true, true);
	ceilLamp8 = LampFactory::CreateLamp(this, Vector3{  0.0f, 10.0f,  8.0f }, true, true);
	floorLamp = LampFactory::CreateLamp(this, Vector3{  6.0f,  0.0f,  0.0f }, false, false);

	//  directional light
	Entity* light = createEntity();
	std::shared_ptr<DirectionalLightComponent> dir_light_comp = light->addComponentByClass<DirectionalLightComponent>();
	dir_light_comp->setColor(Color{ 255, 238, 209, 255 });
	dir_light_comp->setDirection(Vector3::unitY);
	dir_light_comp->setAmbientStrength(0.15f);
	dir_light_comp->setDiffuseStrength(0.0f);


	//  elevator
	//elevator.addModel(&AssetManager::GetModel("crate"));
	//registerObject(&elevator);
	//elevator.setup(Vector3{ 2.5f, 0.1f, 0.0f }, Vector3{ 2.5f, 6.9f, 0.0f }, 4.0f, 2.0f);
	//elevator.pause();


	//  trigger zones
	//elevatorUpZone.setup(Vector3{ 2.5f, 1.0f, 0.0f }, Vector3{ 0.3f, 0.3f, 0.3f });
	//elevatorUpZone.onPlayerEnter.registerObserver(this, Bind_0(&DoomlikeLevelAdvanced::onPlayerEnterElevatorUpZone));
	//enemySpawnZone.setup(Vector3{ 0.0f, 7.5f, 0.0f }, Vector3{ 0.2f, 0.2f, 0.2f });
	//enemySpawnZone.onPlayerEnter.registerObserver(this, Bind_0(&DoomlikeLevelAdvanced::onPlayerEnterEnemySpawnZone));


	//  player spawn point
	spawnPoint = createEntity();
	spawnPoint->setPosition(Vector3{ 9.0f, 0.0f, 0.0f });
	spawnPoint->setRotation(Quaternion::fromEuler(Maths::toRadians(180.0f), 0.0f, 0.0f));
}

void DoomlikeLevelAdvanced::unloadScene()
{
}

void DoomlikeLevelAdvanced::updateScene(float dt)
{
	/*if (elevatorTimer <= 0.0f) return;
	elevatorTimer -= dt;
	if (elevatorTimer <= 0.0f)
	{
		elevator.resume();
	}*/
}

void DoomlikeLevelAdvanced::onPlayerEnterElevatorUpZone()
{
	/*elevatorUpZone.onPlayerEnter.unregisterObserver(this);
	elevatorUpZone.disableZone();
	elevatorTimer = 0.1f;*/
}

void DoomlikeLevelAdvanced::onPlayerEnterEnemySpawnZone()
{
	/*enemySpawnZone.onPlayerEnter.unregisterObserver(this);
	enemySpawnZone.disableZone();*/

	ceilLamp1->getComponentByClass<LampComponent>()->changeStatus(true);
	ceilLamp2->getComponentByClass<LampComponent>()->changeStatus(true);
	ceilLamp3->getComponentByClass<LampComponent>()->changeStatus(true);
	ceilLamp4->getComponentByClass<LampComponent>()->changeStatus(true);
	ceilLamp5->getComponentByClass<LampComponent>()->changeStatus(true);
	ceilLamp6->getComponentByClass<LampComponent>()->changeStatus(true);
	ceilLamp7->getComponentByClass<LampComponent>()->changeStatus(true);
	ceilLamp8->getComponentByClass<LampComponent>()->changeStatus(true);
	floorLamp->getComponentByClass<LampComponent>()->changeStatus(false);

	/*registerObject(new Enemy()).setPosition(Vector3{ -5.0f, 7.5f, -5.0f });
	registerObject(new Enemy()).setPosition(Vector3{ -5.0f, 7.5f,  5.0f });
	registerObject(new Enemy()).setPosition(Vector3{  5.0f, 7.5f, -5.0f });
	registerObject(new Enemy()).setPosition(Vector3{  5.0f, 7.5f,  5.0f });*/
}
