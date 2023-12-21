#pragma once
#include <Rendering/renderer.h>
#include <Rendering/camera.h>

#include <vector>

class Object;
class Light;

class Scene
{
public:
	virtual ~Scene() {} 

	void load(Renderer* renderer_);
	void unload();
	
	virtual void update(float dt) = 0;

	Camera& getCamera();

protected:
	virtual void loadAssets() = 0;
	virtual void loadScene() = 0;
	virtual void unloadScene() = 0;

	void registerObject(Object* object);
	void registerLight(Light* light);

	Renderer* renderer{ nullptr };
	Camera* currentCam{ nullptr };

private:
	bool assetsLoaded{ false };

	std::vector<Object*> sceneregisteredObjects;
	std::vector<Light*> sceneregisteredLights;
};