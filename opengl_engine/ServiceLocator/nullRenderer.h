#pragma once
#include <ServiceLocator/renderer.h>
#include <Rendering/cameraComponent.h>
#include <Utils/Color.h>
#include <Maths/Vector3.h>
#include <Maths/Geometry/box.h>

/**
* The renderer null service provider class.
*/
class NullRenderer : public Renderer
{
public:
	void SetCamera(std::weak_ptr<CameraComponent> camera) override {}
	const std::shared_ptr<CameraComponent> GetCamera() const override { return std::make_shared<CameraComponent>(); } //  pretty sure this is very sus but theorically this function is never called so... alright I guess ?

	void SetClearColor(Color clearColor) override {}
	const Color GetClearColor() const override { return Color::black; }

	void AddMaterial(Material* material) override {}
	void RemoveMaterial(Material* material) override {}

	void AddLight(LightComponent* light) override {}
	void RemoveLight(LightComponent* light) override {}

	void AddModelRenderer(ModelRendererComponent* modelRenderer) override {}
	void RemoveModelRenderer(ModelRendererComponent* modelRenderer) override {}

	void AddText(TextRendererComponent* text) override {}
	void RemoveText(TextRendererComponent* text) override {}

	void AddSprite(SpriteRendererComponent* sprite) override {}
	void RemoveSprite(SpriteRendererComponent* sprite) override {}

	void DrawDebugPoint(const Vector3& pointPosition, const Color& color, float duration) override {}
	void DrawDebugLine(const Vector3& pointA, const Vector3& pointB, const Color& color, float duration) override {}
	void DrawDebugCube(const Box& boxInfos, const Color& color, float duration) override {}
};