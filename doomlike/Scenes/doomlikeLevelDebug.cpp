#include "doomlikeLevelDebug.h"
#include <ServiceLocator/locator.h>
#include <Assets/assetManager.h>

#include <Rendering/Lights/directionalLightComponent.h>
#include <Rendering/Lights/pointLightComponent.h>
#include <Rendering/modelRendererComponent.h>
#include <Physics/AABB/boxAABBColComp.h>

#include <PrefabFactories/floorCeilingFactory.h>
#include <PrefabFactories/stairFactory.h>

#include <Inputs/Input.h>


void DoomlikeLevelDebug::loadScene()
{
	Renderer& renderer = Locator::getRenderer();
	renderer.SetClearColor(Color{ 50, 75, 75, 255 });


	//  prefabs
	FloorCeilingFactory::CreateFloor(this, Vector3{  0.0f, 0.0f,  0.0f }, Vector2{ 10.0f, 10.0f }, false);
	FloorCeilingFactory::CreateFloor(this, Vector3{  0.0f, 0.0f, 10.0f }, Vector2{ 10.0f, 10.0f }, false);
	FloorCeilingFactory::CreateFloor(this, Vector3{ 10.0f, 0.0f, 10.0f }, Vector2{ 10.0f, 10.0f }, false);
	StairFactory::CreateStair(this, StairFactory::StairFacingDirection::StairFacingNegativeX, Vector3{ 4.0f, 0.0f, 2.5f });

	//  entities
	Entity* crate1 = createEntity();
	Entity* crate2 = createEntity();
	Entity* crate3 = createEntity();
	Entity* crate4 = createEntity();
	Entity* crate5 = createEntity();
	Entity* lowcrate1 = createEntity();
	Entity* lowcrate2 = createEntity();
	//Entity* movingPlatform1 = createEntity();
	//Entity* movingPlatform2 = createEntity();
	//Entity* movingPlatform3 = createEntity();
	Entity* trigger_zone = createEntity();
	Entity* dir_light = createEntity();
	Entity* point_light = createEntity();

	crate1->setPosition(Vector3{ 2.0f, 0.5f, 0.0f });
	crate2->setPosition(Vector3{ 3.0f, 1.0f, 13.0f });
	crate2->setScale(Vector3{ 0.5f, 2.0f, 2.0f });
	crate3->setPosition(Vector3{ 9.5f, 0.5f, 9.0f });
	crate4->setPosition(Vector3{ 2.5f, 3.0f, 7.5f });
	crate5->setPosition(Vector3{ 12.0f, 2.1f, 12.0f });
	crate5->setScale(Vector3{ 1.0f, 0.1f, 1.0f });
	lowcrate1->setPosition(Vector3{ 8.0f, 0.1f, 15.5f });
	lowcrate1->setScale(Vector3{ 1.0f, 0.2f, 1.0f });
	lowcrate2->setPosition(Vector3{ 9.0f, 0.3f, 15.5f });
	lowcrate2->setScale(Vector3{ 1.0f, 0.2f, 1.0f });
	trigger_zone->setPosition(Vector3{ 12.0f, 1.0f, 12.0f });

	//  components
	crate1->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	crate2->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	crate3->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	crate4->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	crate5->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	lowcrate1->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	lowcrate2->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	//movingPlatform1->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	//movingPlatform2->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	//movingPlatform3->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));

	crate1->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("solid");
	crate2->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("solid");
	crate3->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("solid");
	crate4->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("solid");
	crate5->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("solid");
	lowcrate1->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("solid");
	lowcrate2->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("solid");
	std::shared_ptr<BoxAABBColComp> trigger_zone_col = trigger_zone->addComponentByClass<BoxAABBColComp>();
	trigger_zone_col->setCollisionChannel("trigger_zone");
	trigger_zone_col->setCollisionType(CollisionType::Trigger);


	//movingPlatform1.setup(Vector3{ 6.0f, 1.9f, 2.5f }, Vector3{ 9.0f, 3.0f, 11.5f }, 3.0f, 2.0f);
	//movingPlatform1.pause();
	//movingPlatform2.setup(Vector3{ -7.0f, 0.0f, -7.0f }, Vector3{ -7.0f, 0.0f, 7.0f }, 7.0f);
	//movingPlatform3.setup(Vector3{10.0f, -3.0f, 3.0f}, Vector3{10.0f, 5.0f, 3.0f}, 5.0f);

	std::shared_ptr<DirectionalLightComponent> dir_light_comp = dir_light->addComponentByClass<DirectionalLightComponent>();
	dir_light_comp->setColor(Color::white);
	dir_light_comp->setDirection(Vector3::normalize(Vector3{ 0.5f, -1.0f, 0.75f }));
	dir_light_comp->setAmbientStrength(0.1f);
	dir_light_comp->setDiffuseStrength(0.7f);

	std::shared_ptr<PointLightComponent> point_light_comp = point_light->addComponentByClass<PointLightComponent>();
	point_light_comp->setColor(Color::red);
	point_light_comp->setOffset(Vector3{ 8.0f, 1.0f, 9.0f });


	//  player spawn point
	spawnPoint = createEntity();
	spawnPoint->setPosition(Vector3{ 8.0f, 0.0f, 9.0f });
	spawnPoint->setRotation(Quaternion::fromEuler(Maths::toRadians(135.0f), 0.0f, 0.0f));
}

void DoomlikeLevelDebug::unloadScene()
{
}

void DoomlikeLevelDebug::updateScene(float dt)
{
	if (Input::IsKeyPressed(GLFW_KEY_H))
	{
		//movingPlatform1.resume();
	}
}