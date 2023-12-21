#include "scene.h"

void Scene::load(Renderer* renderer_) 
{ 
	renderer = renderer_; 
	if (!assetsLoaded)
	{
		loadAssets();
		assetsLoaded = true;
	}
	loadScene();
}

void Scene::unload()
{
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

Camera& Scene::getCamera() 
{ 
	return *currentCam; 
}

void Scene::registerObject(Object* object)
{
	sceneregisteredObjects.push_back(object);
	renderer->addObject(object);
}

void Scene::registerLight(Light* light)
{
	sceneregisteredLights.push_back(light);
	renderer->addLight(light);
}