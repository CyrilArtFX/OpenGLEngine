#include "scene.h"
#include <Physics/physics.h>

void Scene::load(Renderer* renderer_) 
{ 
	renderer = renderer_; 

	loadScene();
}

void Scene::unload()
{
	//  TODO: remove this when a proper integrations of collisions as components is done
	Physics::ClearAllCollisions();

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