#pragma once
#include <ServiceLocator/renderer.h>

#include <Utils/color.h>
#include <Maths/matrix4.h>
#include <Maths/vector3.h>
#include <Maths/vector2Int.h>
#include <Maths/vector4.h>

#include <Rendering/cameraComponent.h>
#include <Rendering/material.h>
#include <Rendering/Lights/lightComponent.h>
#include <Rendering/modelRendererComponent.h>
#include <Rendering/Text/textRendererComponent.h>
#include <Rendering/Hud/spriteRendererComponent.h>

#include <vector>
#include <unordered_map>


//  would be cool if I find a better way to do this but it works for now
const std::unordered_map<LightType, int> LIGHTS_LIMITS
{
	{EDirectionalLight, 1},
	{EPointLight, 16},
	{ESpotLight, 8}
};

const int TEXT_CHARS_LIMIT{ 200 };


/**
* The renderer service provider class.
*/
class RendererOpenGL : public Renderer
{
public:
	void SetCamera(CameraComponent* camera) override;
	const CameraComponent* GetCamera() const override;

	void SetClearColor(Color clearColor_) override;
	const Color GetClearColor() const override;

	void AddMaterial(Material* material) override;
	void RemoveMaterial(Material* material) override;

	void AddLight(LightComponent* light) override;
	void RemoveLight(LightComponent* light) override;

	void AddModelRenderer(ModelRendererComponent* modelRenderer) override;
	void RemoveModelRenderer(ModelRendererComponent* modelRenderer) override;

	void AddText(TextRendererComponent* text) override;
	void RemoveText(TextRendererComponent* text) override;

	void AddSprite(SpriteRendererComponent* sprite) override;
	void RemoveSprite(SpriteRendererComponent* sprite) override;




private:
	CameraComponent* selectCurrentCam();

	std::unordered_map<LightType, std::vector<LightComponent*>> lights;
	std::unordered_map<Shader*, std::vector<Material*>> materials;
	std::vector<ModelRendererComponent*> modelRenderers;
	std::vector<TextRendererComponent*> texts;
	std::vector<SpriteRendererComponent*> sprites;

	Color clearColor{ Color::black };

	CameraComponent* activeCamera{ nullptr };
	CameraComponent* defaultCamera{ nullptr };
	CameraComponent* debugCamera{ nullptr };

	Vector2Int windowSize;

	bool debugActivated;

	




//  exclusive to engine which is the only class to access the full renderer
public:
	void initializeRenderer(Color clearColor_, Vector2Int windowSize_, CameraComponent* defaultCamera_);

	void setDebugCamera(CameraComponent* debugCamera_);
	void setDebugActivated(bool debugActivated_);

	void draw();

	void setWindowSize(Vector2Int windowSize_);

	bool drawDebugMode{ false };
};

