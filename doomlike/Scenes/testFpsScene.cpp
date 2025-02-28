#include "testFpsScene.h"
#include <ServiceLocator/locator.h>
#include <ServiceLocator/physics.h>
#include <Physics/AABB/boxAABBColComp.h>
#include <Physics/ObjectChannels/collisionChannels.h>

TestFpsScene::TestFpsScene()
{
}

void TestFpsScene::loadScene()
{
	Renderer& renderer = Locator::getRenderer();

	renderer.SetClearColor(Color{ 50, 75, 75, 255 });


	//  objects
	ground.addModel(&AssetManager::GetModel("ground"));
	crate1.addModel(&AssetManager::GetModel("crate"));
	crate2.addModel(&AssetManager::GetModel("crate"));
	crate3.addModel(&AssetManager::GetModel("crate"));
	target1.addModel(&AssetManager::GetModel("crate"));
	testMesh.addModel(&AssetManager::GetModel("taxi"));

	registerObject(&ground);
	registerObject(&crate1);
	registerObject(&crate2);
	registerObject(&crate3);
	registerObject(&target1);
	registerObject(&testMesh);

	ground.setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	crate1.setPosition(Vector3{ 2.0f, 0.5f, 0.0f });
	crate2.setPosition(Vector3{ -1.0f, 0.5f, 3.0f });
	crate3.setPosition(Vector3{ -3.5f, 0.5f, -1.0f });
	target1.setPosition(Vector3{ 0.0f, 1.5f, -5.0f });
	target1.setScale(Vector3{ 1.0f, 1.0f, 0.1f });
	testMesh.setPosition(Vector3{ -7.0f, 1.0f, 0.0f });
	testMesh.setScale(0.01f);
	testMesh.setRotation(Quaternion{ Vector3::unitX, Maths::toRadians(-90.0f) });


	//  collisions
	Physics& physics = Locator::getPhysics();

	physics.CreateCollisionComponent(new BoxAABBColComp(Box::one, &crate1, false, "solid"));
	physics.CreateCollisionComponent(new BoxAABBColComp(Box::one, &crate2, false, "solid"));
	physics.CreateCollisionComponent(new BoxAABBColComp(Box::one, &crate3, false, "solid"));
	physics.CreateCollisionComponent(new BoxAABBColComp(Box{ Vector3{0.0f, -0.5f, 0.0f}, Vector3{5.0f, 0.5f, 5.0f} }, &ground, false, "solid"));

	RaycastHitInfos out_raycast;
	physics.LineRaycast(Vector3{ -1.0f, 3.5f, 3.0f }, Vector3{ -1.0f, -1.5f, 3.0f }, CollisionChannels::GetRegisteredTestChannel("TestEverything"), out_raycast);
	physics.LineRaycast(Vector3{ -4.5f, 0.5f, -3.0f }, Vector3{ 0.0f, 0.5f, 5.0f }, CollisionChannels::GetRegisteredTestChannel("TestEverything"), out_raycast, -1.0f);
	physics.AABBRaycast(Vector3{ 4.2f, 0.3f, -2.0f }, Box::one);


	//  lights
	Vector3 dir_light{ 0.5f, -1.0f, 0.75f };
	dir_light.normalize();
	dirLight.load(Color::white, dir_light, 0.1f, 0.7f);
	registerLight(&dirLight);
}

void TestFpsScene::unloadScene()
{
}

void TestFpsScene::updateScene(float dt)
{
}
