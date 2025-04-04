#include "testFpsScene.h"
#include <ServiceLocator/locator.h>
#include <Assets/assetManager.h>

#include <Rendering/Lights/directionalLightComponent.h>
#include <Rendering/modelRendererComponent.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/ObjectChannels/collisionChannels.h>

#include <PrefabFactories/floorCeilingFactory.h>


void TestFpsScene::loadScene()
{
	Renderer& renderer = Locator::getRenderer();
	renderer.SetClearColor(Color{ 50, 75, 75, 255 });


	//  prefabs
	FloorCeilingFactory::CreateFloor(this, Vector3{ 0.0f, 0.0f, 0.0f }, Vector2{ 10.0f, 10.0f }, false);

	//  entities
	Entity* crate1 = createEntity();
	Entity* crate2 = createEntity();
	Entity* crate3 = createEntity();
	Entity* target = createEntity();
	Entity* taxi = createEntity();
	Entity* light = createEntity();

	crate1->setPosition(Vector3{ 2.0f, 0.5f, 0.0f });
	crate2->setPosition(Vector3{ -1.0f, 0.5f, 3.0f });
	crate3->setPosition(Vector3{ -3.5f, 0.5f, -1.0f });
	target->setPosition(Vector3{ 0.0f, 1.5f, -5.0f });
	target->setScale(Vector3{ 1.0f, 1.0f, 0.1f });
	taxi->setPosition(Vector3{ -7.0f, 1.0f, 0.0f });
	taxi->setScale(0.01f);
	taxi->setRotation(Quaternion{ Vector3::unitX, Maths::toRadians(-90.0f) });

	//  components
	crate1->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	crate2->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	crate3->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	target->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("crate"));
	taxi->addComponentByClass<ModelRendererComponent>()->setModel(&AssetManager::GetModel("taxi"));

	crate1->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("solid");
	crate2->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("solid");
	crate3->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("solid");
	target->addComponentByClass<BoxAABBColComp>()->setCollisionChannel("solid");

	std::shared_ptr<DirectionalLightComponent> dir_light_comp = light->addComponentByClass<DirectionalLightComponent>();
	dir_light_comp->setColor(Color::white);
	dir_light_comp->setDirection(Vector3::normalize(Vector3{ 0.5f, -1.0f, 0.75f }));
	dir_light_comp->setAmbientStrength(0.1f);
	dir_light_comp->setDiffuseStrength(0.7f);

	//  raycast tests
	Physics& physics = Locator::getPhysics();
	RaycastHitInfos out_raycast;
	physics.LineRaycast(Vector3{ -1.0f, 3.5f, 3.0f }, Vector3{ -1.0f, -1.5f, 3.0f }, CollisionChannels::GetRegisteredTestChannel("TestEverything"), out_raycast);
	physics.LineRaycast(Vector3{ -4.5f, 0.5f, -3.0f }, Vector3{ 0.0f, 0.5f, 5.0f }, CollisionChannels::GetRegisteredTestChannel("TestEverything"), out_raycast, -1.0f);
	physics.AABBRaycast(Vector3{ 4.2f, 0.3f, -2.0f }, Box::one);
}

void TestFpsScene::unloadScene()
{
}