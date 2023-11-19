#pragma once
#include <memory>
#include <Rendering/renderer.h>

class Scene
{
public:
	Scene() : renderer() {}
	virtual ~Scene() {} 

	virtual void load(std::weak_ptr<Renderer> renderer_) = 0;
	virtual void unload() = 0; 
	
	virtual void update(float dt) = 0;

	//  should be packed into a single function for simplicity
	virtual void processInputs(GLFWwindow* glWindow, float dt) = 0;
	virtual void processMouse(float xOffset, float yOffset) = 0;
	virtual void processScroll(float scrollOffset) = 0;

protected:
	std::shared_ptr<Renderer> renderer; 
};