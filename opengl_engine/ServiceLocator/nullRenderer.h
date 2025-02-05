#pragma once
#include <ServiceLocator/renderer.h>
#include <Rendering/camera.h>
#include <Utils/Color.h>

/**
* The renderer null service provider class.
*/
class NullRenderer : public Renderer
{
public:
	void SetCamera(Camera* camera) override {}
	const Camera& GetCamera() const override { return *new Camera(); } //  pretty sure this is very sus but theorically this function is never called so... alright I guess ?

	void SetClearColor(Color clearColor) override {}
	const Color GetClearColor() const override { return Color::black; }

	void AddMaterial(Material* material) override {}
	void RemoveMaterial(Material* material) override {}

	void AddLight(Light* light) override {}
	void RemoveLight(Light* light) override {}

	void AddModelRenderer(ModelRendererComponent* modelRenderer) override {}
	void RemoveModelRenderer(ModelRendererComponent* modelRenderer) override {}

	void AddText(TextRendererComponent* text) override {}
	void RemoveText(TextRendererComponent* text) override {}

	void AddSprite(SpriteRendererComponent* sprite) override {}
	void RemoveSprite(SpriteRendererComponent* sprite) override {}
};