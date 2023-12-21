#include "testFpsScene.h"

TestFpsScene::TestFpsScene()
{
}

void TestFpsScene::loadScene()
{
	renderer->setClearColor(Color{ 50, 75, 75, 255 });


	//  objects
	ground.addModel(&AssetManager::GetModel("ground"));
	crate1.addModel(&AssetManager::GetModel("crate"));
	crate2.addModel(&AssetManager::GetModel("crate"));
	crate3.addModel(&AssetManager::GetModel("crate"));
	testMesh.addModel(&AssetManager::GetModel("taxi"));

	registerObject(&ground);
	registerObject(&crate1);
	registerObject(&crate2);
	registerObject(&crate3);
	registerObject(&testMesh);

	ground.setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	crate1.setPosition(Vector3{ 2.0f, 0.5f, 0.0f });
	crate2.setPosition(Vector3{ -1.0f, 0.5f, 3.0f });
	crate3.setPosition(Vector3{ -3.5f, 0.5f, -1.0f });
	testMesh.setPosition(Vector3{ -7.0f, 1.0f, 0.0f });
	testMesh.setScale(0.01f);
	testMesh.setRotation(Quaternion{ Vector3::unitX, Maths::toRadians(-90.0f) });


	//  lights
	Vector3 dir_light{ 0.5f, -1.0f, 0.75f };
	dir_light.normalize();
	dirLight.load(Color::white, dir_light, 0.1f, 0.7f);
	registerLight(&dirLight);
}

void TestFpsScene::unloadScene()
{
}

void TestFpsScene::update(float dt)
{
}
