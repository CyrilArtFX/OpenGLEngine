#include "demoreelScenePhysics.h"
#include <ServiceLocator/locator.h>
#include <Assets/assetManager.h>
#include <Inputs/Input.h>
#include <Physics/ObjectChannels/collisionChannels.h>

#include <Rendering/Lights/directionalLightComponent.h>
#include <Rendering/modelRendererComponent.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/rigidbodyComponent.h>
#include <GameComponents/movingPlatformComponent.h>

#include <PrefabFactories/floorCeilingFactory.h>
#include <PrefabFactories/wallFactory.h>
#include <PrefabFactories/stairFactory.h>
#include <PrefabFactories/lampFactory.h>

using WallFactory::WallFacingDirection;


void DemoreelScenePhysics::loadScene()
{
	Renderer& renderer = Locator::getRenderer();
	renderer.SetClearColor(Color{ 0, 5, 20, 255 });


	//  prefabs
	FloorCeilingFactory::CreateFloor(this, Vector3{ 0.0f, 0.0f, 0.0f }, Vector2{ 20.0f, 10.0f }, false);
	FloorCeilingFactory::CreateCeiling(this, Vector3{ 0.0f, 6.0f, 0.0f }, Vector2{ 20.0f, 10.0f });
	FloorCeilingFactory::CreateFloor(this, Vector3{ 7.5f, 2.0f, 0.0f }, Vector2{ 5.0f, 10.0f }, true);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeX, Vector3{ 10.0f, 3.0f, 0.0f }, Vector2{ 10.0f, 6.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveX, Vector3{ -10.0f, 3.0f, 0.0f }, Vector2{ 10.0f, 6.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeZ, Vector3{ 0.0f, 3.0f, 5.0f }, Vector2{ 20.0f, 6.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingPositiveZ, Vector3{ 0.0f, 3.0f, -5.0f }, Vector2{ 20.0f, 6.0f }, false);
	WallFactory::CreateWall(this, WallFacingDirection::WallFacingNegativeX, Vector3{ 5.0f, 1.0f, 0.0f }, Vector2{ 10.0f, 2.0f }, true);
	StairFactory::CreateStair(this, StairFactory::StairFacingDirection::StairFacingNegativeX, Vector3{ 4.0f, 0.0f, 3.0f });
	LampFactory::CreateLamp(this, Vector3{ -1.0f, 0.0f, 0.5f }, 9.0f, false);


	//  entities
	Entity* light = createEntity();
	movingPlatform = createEntity();
	movingPlatform->setPosition(Vector3{ 3.5f, 2.0f, -2.5f });
	movingPlatform->setScale(Vector3{ 2.0f, 0.2f, 2.0f });

	//  components
	std::shared_ptr<DirectionalLightComponent> dir_light_comp = light->addComponentByClass<DirectionalLightComponent>();
	dir_light_comp->setColor(Color::white);
	dir_light_comp->setDirection(Vector3::normalize(Vector3{ 0.5f, -1.0f, -0.75f }));
	dir_light_comp->setAmbientStrength(0.4f);
	dir_light_comp->setDiffuseStrength(0.0f);

	movingPlatform->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	movingPlatform->addComponentByClass<MovingPlatformComponent>()->setupMovingPlatform(Vector3{ 3.5f, 2.0f, -2.5f }, Vector3{ -7.5f, 2.0f, -2.5f }, 4.0f);
	movingPlatform->getComponentByClass<MovingPlatformComponent>()->pauseMovement();


	//  player spawn point
	spawnPoint = createEntity();
	spawnPoint->setPosition(Vector3{ -5.0f, 0.0f, 2.0f });
}

void DemoreelScenePhysics::unloadScene()
{
}

void DemoreelScenePhysics::updateScene(float dt)
{
	if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		movingPlatform->getComponentByClass<MovingPlatformComponent>()->resumeMovement();
	}

	if (Input::IsKeyPressed(GLFW_KEY_C))
	{
		Entity* test_physic_entity = createEntity();
		test_physic_entity->setPosition(Vector3{ -7.5f, 5.0f, 3.0f });
		test_physic_entity->setScale(0.3f);
		test_physic_entity->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
		test_physic_entity->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("test_physic_channel");
		std::shared_ptr<RigidbodyComponent> test_rigidbody = test_physic_entity->addComponentByClass<RigidbodyComponent>();
		test_rigidbody->associateCollision(test_physic_entity->getComponentByClass<BoxAABBColComp>());
		test_rigidbody->setPhysicsActivated(true);
		test_rigidbody->setUseGravity(true);
		test_rigidbody->setTestChannels({ "solid", "test_physic_channel" });
	}
}
