#include "scene.h"
#include <Physics/physics.h>
#include <algorithm>
#include <iostream>

void Scene::load(Renderer* renderer_) 
{ 
	renderer = renderer_; 

	loadScene();
}

void Scene::unload(bool exitGame)
{
	//  TODO: remove this when a proper integrations of collisions as components is done
	Physics::ClearAllCollisions(exitGame);

	for (auto object : sceneregisteredObjects)
	{
		renderer->removeObject(object);
	}
	sceneregisteredObjects.clear();

	for (auto light : sceneregisteredLights)
	{
		renderer->removeLight(light);
	}
	sceneregisteredLights.clear();

	unloadScene();
}

void Scene::update(float dt)
{
	if (firstFrame)
	{
		firstFrame = false;
		return;
	}

	updateScene(dt);

	for (auto object : sceneregisteredObjects)
	{
		object->updateObject(dt);
	}
}

Camera& Scene::getCamera() 
{ 
	return *currentCam; 
}

Object& Scene::registerObject(Object* object)
{
	sceneregisteredObjects.push_back(object);
	object->load();
	renderer->addObject(object);
	return *sceneregisteredObjects.back();
}

Light& Scene::registerLight(Light* light)
{
	sceneregisteredLights.push_back(light);
	renderer->addLight(light);
	return *sceneregisteredLights.back();
}

void Scene::unregisterObject(Object* object)
{
	auto iter = std::find(sceneregisteredObjects.begin(), sceneregisteredObjects.end(), object);
	if (iter == sceneregisteredObjects.end())
	{
		std::cout << "Tried to unregister a scene object that was not registered.\n";
		return;
	}

	renderer->removeObject(object);

	sceneregisteredObjects.erase(iter);
}

void Scene::unregisterLight(Light* light)
{
	auto iter = std::find(sceneregisteredLights.begin(), sceneregisteredLights.end(), light);
	if (iter == sceneregisteredLights.end())
	{
		std::cout << "Tried to unregister a scene light that was not registered.\n";
		return;
	}

	renderer->removeLight(light);

	sceneregisteredLights.erase(iter);
}
