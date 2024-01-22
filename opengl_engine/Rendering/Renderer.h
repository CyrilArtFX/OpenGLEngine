#pragma once
#include <Utils/color.h>
#include <Maths/matrix4.h>
#include <Maths/vector3.h>
#include <Maths/vector2Int.h>

#include "camera.h"
#include <Objects/object.h>
#include <Objects/Lights/light.h>
#include "material.h"

#include <vector>
#include <unordered_map>


class Renderer
{
public:
	Renderer();
	void createRenderer(Color clearColor_, Vector2Int windowSize_);

	void draw();


	void setCamera(Camera* camera);
	inline const Camera& getCamera() const { return *currentCam; }

	void addMaterial(Material* material);
	void removeMaterial(Material* material);

	void addLight(Light* light);
	void addObject(Object* object);
	void removeLight(Light* light);
	void removeObject(Object* object);


	inline void setClearColor(Color newClearColor) { clearColor = newClearColor; }
	inline Color getClearColor() { return clearColor; }

	inline void setWindowSize(Vector2Int newWindowSize) { windowSize = newWindowSize; }

private:
	std::unordered_map<LightType, std::vector<Light*>> lights;
	std::vector<Object*> objects;
	std::unordered_map<Shader*, std::vector<Material*>> materials;

	Color clearColor{ Color::black };

	Camera* currentCam;
	Vector2Int windowSize;

	//  would be cool if I find a better way to do this but it works for now
	const std::unordered_map<LightType, int> lightsLimits
	{
		{Directionnal, 1},
		{Point, 16},
		{Spot, 8}
	};


public:
	bool drawDebugMode{ false };
};

