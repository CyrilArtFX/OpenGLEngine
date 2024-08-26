#pragma once
#include <Rendering/camera.h>

#include <vector>

class Object;
class Light;

class Scene
{
public:
	virtual ~Scene() {} 

	void load();
	void unload(bool exitGame);

	void update(float dt);
	
	virtual void updateScene(float dt) = 0;

	Camera& getCamera();

	/* Register Object
	* Register an object as a scene object.
	* Will add this object to the renderer and will properly remove it at scene unloading.
	*/
	Object& registerObject(Object* object);

	/* Register Light
	* Register a light as a scene light.
	* Will add this light to the renderer and will properly remove it at scene unloading.
	*/
	Light& registerLight(Light* light);

	/* Unregister Object
	* Unregister an object from the scene objects.
	* Will properly remove this object from the renderer.
	*/
	void unregisterObject(Object* object);

	/* Unregister Light
	* Unregister a light from the scene lights.
	* Will properly remove this light from the renderer.
	*/
	void unregisterLight(Light* light);

protected:
	virtual void loadScene() = 0;
	virtual void unloadScene() = 0;

	Camera* currentCam{ nullptr };

private:
	std::vector<Object*> sceneregisteredObjects;
	std::vector<Light*> sceneregisteredLights;

	bool firstFrame{ true };
};