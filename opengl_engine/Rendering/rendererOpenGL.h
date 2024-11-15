#pragma once
#include <ServiceLocator/renderer.h>

#include <Utils/color.h>
#include <Maths/matrix4.h>
#include <Maths/vector3.h>
#include <Maths/vector2Int.h>
#include <Maths/vector4.h>

#include "camera.h"
#include <Objects/object.h>
#include <Objects/Lights/light.h>
#include <Rendering/material.h>
#include <Rendering/Text/textRendererComponent.h>

#include <vector>
#include <unordered_map>


//  would be cool if I find a better way to do this but it works for now
const std::unordered_map<LightType, int> LIGHTS_LIMITS
{
	{EDirectionalLight, 1},
	{EPointLight, 16},
	{ESpotLight, 8}
};

const int TEXT_CHARS_LIMIT{ 512 };


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

	void AddText(TextRendererComponent* text) override;
	void RemoveText(TextRendererComponent* text) override;




private:
	std::unordered_map<LightType, std::vector<Light*>> lights;
	std::vector<Object*> objects;
	std::unordered_map<Shader*, std::vector<Material*>> materials;
	std::vector<TextRendererComponent*> texts;

	Color clearColor{ Color::black };

	Camera* currentCam;
	Vector2Int windowSize;

	




//  exclusive to engine which is the only class to access the full renderer
public:
	void initializeRenderer(Color clearColor_, Vector2Int windowSize_);

	void draw();

	void setWindowSize(Vector2Int windowSize_);

	bool drawDebugMode{ false };
};

