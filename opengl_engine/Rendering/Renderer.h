#pragma once
#include <Utils/Color.h>
#include <Maths/Matrix4.h>
#include <Maths/Vector3.h>

#include <Objects/object.h>
#include <Objects/Lights/light.h>
#include "material.h"

#include <vector>
#include <unordered_map>


class Renderer
{
public:
	Renderer(Color clearColor_);
	Renderer(const Renderer&) = delete;
	Renderer operator=(const Renderer&) = delete;

	void draw(Matrix4 view, Matrix4 projection, Vector3 viewPos);


	void addLight(std::weak_ptr<Light> light, LightType type);
	void addObject(std::weak_ptr<Object> object, Material& mat);


	inline void setClearColor(Color newClearColor) { clearColor = newClearColor; }
	inline Color getClearColor() { return clearColor; }

private:
	std::unordered_map<LightType, std::vector<std::shared_ptr<Light>>> lights;
	std::unordered_map<Material&, std::vector<std::shared_ptr<Object>>> objects;

	Color clearColor;


	//  would be cool if I find a better way to do this but it works for now
	const std::unordered_map<LightType, int> lights_limits
	{
		{Directionnal, 1},
		{Point, 16},
		{Spot, 8}
	};
};

