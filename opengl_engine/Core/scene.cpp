#include "scene.h"
#include <ServiceLocator/locator.h>
#include <Objects/object.h>
#include <Objects/Lights/light.h>
#include <algorithm>

void Scene::load() 
{ 
	loadScene();
}

void Scene::unload(bool exitGame)
{
	//  TODO: remove this when a proper integrations of collisions as components is done
	Locator::getPhysics().ClearAllCollisions(exitGame);

	Renderer& renderer = Locator::getRenderer();

	for (auto object : sceneregisteredObjects)
	{
		renderer.RemoveObject(object);
	}
	sceneregisteredObjects.clear();

	for (auto light : sceneregisteredLights)
	{
		renderer.RemoveLight(light);
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
	Locator::getRenderer().AddObject(object);
	return *sceneregisteredObjects.back();
}

Light& Scene::registerLight(Light* light)
{
	sceneregisteredLights.push_back(light);
	Locator::getRenderer().AddLight(light);
	return *sceneregisteredLights.back();
}

void Scene::unregisterObject(Object* object)
{
	auto iter = std::find(sceneregisteredObjects.begin(), sceneregisteredObjects.end(), object);
	if (iter == sceneregisteredObjects.end())
	{
		Locator::getLog().LogMessage_Category("Scene: Tried to unregister a scene object that was not registered.", LogCategory::Error);
		return;
	}

	Locator::getRenderer().RemoveObject(object);

	sceneregisteredObjects.erase(iter);
}

void Scene::unregisterLight(Light* light)
{
	auto iter = std::find(sceneregisteredLights.begin(), sceneregisteredLights.end(), light);
	if (iter == sceneregisteredLights.end())
	{
		Locator::getLog().LogMessage_Category("Scene: Tried to unregister a scene light that was not registered.", LogCategory::Error);
		return;
	}

	Locator::getRenderer().RemoveLight(light);

	sceneregisteredLights.erase(iter);
}
