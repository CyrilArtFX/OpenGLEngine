#pragma once
#include <Utils/color.h>
#include <Maths/matrix4.h>
#include <Maths/vector3.h>

#include "camera.h"
#include <Core/window.h>
#include <Objects/object.h>
#include <Objects/Lights/light.h>
#include "material.h"

#include <vector>
#include <unordered_map>


class Renderer
{
public:
	Renderer(Color clearColor_, const Window& window);
	Renderer() = delete;
	Renderer(const Renderer&) = delete;
	Renderer operator=(const Renderer&) = delete;

	void draw();


	void setCamera(std::weak_ptr<Camera> camera);

	void addLight(std::weak_ptr<Light> light, LightType type);
	void addObject(std::weak_ptr<Object> object, std::shared_ptr<Material>);


	inline void setClearColor(Color newClearColor) { clearColor = newClearColor; }
	inline Color getClearColor() { return clearColor; }

private:
	std::unordered_map<LightType, std::vector<std::shared_ptr<Light>>> lights;
	std::unordered_map<std::shared_ptr<Material>, std::vector<std::shared_ptr<Object>>> objects;

	Color clearColor;

	std::shared_ptr<Camera> currentCam;
	const Window& windowRef;

	//  would be cool if I find a better way to do this but it works for now
	const std::unordered_map<LightType, int> lights_limits
	{
		{Directionnal, 1},
		{Point, 16},
		{Spot, 8}
	};
};

