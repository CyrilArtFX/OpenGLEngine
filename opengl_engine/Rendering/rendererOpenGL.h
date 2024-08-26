#pragma once
#include <ServiceLocator/renderer.h>

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

/**
* The renderer service provider class.
*/
class RendererOpenGL : public Renderer
{
public:
	void SetCamera(Camera* camera) override;
	const Camera& GetCamera() const override;

	void SetClearColor(Color clearColor_) override;
	const Color GetClearColor() const override;

	void AddMaterial(Material* material) override;
	void RemoveMaterial(Material* material) override;

	void AddLight(Light* light) override;
	void RemoveLight(Light* light) override;

	void AddObject(Object* object) override;
	void RemoveObject(Object* object) override;




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
		{EDirectionalLight, 1},
		{EPointLight, 16},
		{ESpotLight, 8}
	};




//  exclusive to engine which is the only class to access the full renderer
public:
	void initializeRenderer(Color clearColor_, Vector2Int windowSize_);

	void draw();

	void setWindowSize(Vector2Int windowSize_);

	bool drawDebugMode{ false };
};

