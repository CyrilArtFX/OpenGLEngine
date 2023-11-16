#pragma once
#include <memory>
#include <Rendering/renderer.h>

class Scene
{
public:
	Scene(std::weak_ptr<Renderer> renderer_) : renderer(renderer_.lock()) {}
	virtual ~Scene() {} 

	virtual void load() = 0; 
	virtual void unload() = 0; 
	
	virtual void update(float dt) = 0;

protected:
	std::shared_ptr<Renderer> renderer; 
};