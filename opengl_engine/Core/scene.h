#pragma once
#include <memory>
#include <Rendering/renderer.h>
#include <Rendering/camera.h>

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {} 

	virtual void load(Renderer* renderer_) = 0;
	virtual void unload() = 0; 
	
	virtual void update(float dt) = 0;

	inline Camera& getCamera() { return *currentCam; }

protected:
	Renderer* renderer; 
	Camera* currentCam;
};