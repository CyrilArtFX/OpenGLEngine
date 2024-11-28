#pragma once
#include "hudComponent.h"

class Texture;

/** Sprite Renderer Component
*/
class SpriteRendererComponent : public HudComponent
{
public:
	SpriteRendererComponent();
	SpriteRendererComponent(const SpriteRendererComponent& other);
	~SpriteRendererComponent();
	SpriteRendererComponent& operator=(const SpriteRendererComponent& other) = delete;

	void setSpriteDatas(const Texture& spriteTexture_, const Vector2& pivot_, const Vector2& screenPos_, const Vector2& scale_, const float rotAngle_, const Color& tintColor_);

	void setSpriteTexture(const Texture& spriteTexture_);
	const Texture& getSpriteTexture() const;

	Vector2 getSize() const override;

	bool canDraw() const;
	
protected:
	bool needToComputeMatrix() const override;

private:
	const Texture* spriteTexture;
};