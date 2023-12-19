#pragma once
#include <memory>
#include <Rendering/renderer.h>
#include <Rendering/camera.h>

class Scene
{
public:
	Scene() : renderer() {}
	virtual ~Scene() {} 

	virtual void load(std::weak_ptr<Renderer> renderer_) = 0;
	virtual void unload() = 0; 
	
	virtual void update(float dt) = 0;

	inline std::weak_ptr<Camera> getCamera() { return currentCam; }

protected:
	std::shared_ptr<Renderer> renderer; 
	std::shared_ptr<Camera> currentCam;
};