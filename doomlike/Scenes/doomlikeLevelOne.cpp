#include "doomlikeLevelOne.h"

DoomlikeLevelOne::DoomlikeLevelOne()
{
}

void DoomlikeLevelOne::loadScene()
{
	renderer->setClearColor(Color{ 50, 75, 75, 255 });


	//  objects
	ground1.addModel(&AssetManager::GetModel("ground"));
	ground2.addModel(&AssetManager::GetModel("ground"));
	ground3.addModel(&AssetManager::GetModel("ground"));
	crate1.addModel(&AssetManager::GetModel("crate"));
	crate2.addModel(&AssetManager::GetModel("crate"));
	crate3.addModel(&AssetManager::GetModel("crate"));

	registerObject(&ground1);
	registerObject(&ground2);
	registerObject(&ground3);
	registerObject(&crate1);
	registerObject(&crate2);
	registerObject(&crate3);

	ground1.setPosition(Vector3{ 0.0f, 0.0f, 0.0f });
	ground2.setPosition(Vector3{ 0.0f, 0.0f, 10.0f });
	ground3.setPosition(Vector3{ 10.0f, 0.0f, 10.0f });
	crate1.setPosition(Vector3{ 2.0f, 0.5f, 0.0f });
	crate2.setPosition(Vector3{ 3.0f, 0.5f, 13.0f });
	crate3.setPosition(Vector3{ 9.5f, 0.5f, 9.0f });


	//  lights
	Vector3 dir_light{ -0.5f, -1.0f, 0.75f };
	dir_light.normalize();
	dirLight.load(Color::white, dir_light, 0.1f, 0.7f);
	registerLight(&dirLight);

	pointLight1.load(Color::red, Vector3{ 8.0f, 1.0f, 9.0f });
	registerLight(&pointLight1);
}

void DoomlikeLevelOne::update(float dt)
{
}

void DoomlikeLevelOne::unloadScene()
{
}
