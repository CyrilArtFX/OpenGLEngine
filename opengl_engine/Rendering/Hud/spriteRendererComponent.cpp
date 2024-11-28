#include "spriteRendererComponent.h"
#include <Rendering/texture.h>
#include <Maths/Vector2Int.h>
#include <ServiceLocator/locator.h>
#include <ServiceLocator/renderer.h>


SpriteRendererComponent::SpriteRendererComponent() : HudComponent(), spriteTexture(nullptr)
{
	Locator::getRenderer().AddSprite(this);
}

SpriteRendererComponent::SpriteRendererComponent(const SpriteRendererComponent& other) : HudComponent(other), spriteTexture(other.spriteTexture)
{
	Locator::getRenderer().AddSprite(this);
}

SpriteRendererComponent::~SpriteRendererComponent()
{
	Locator::getRenderer().RemoveSprite(this);
}


void SpriteRendererComponent::setSpriteDatas(const Texture& spriteTexture_, const Vector2& pivot_, const Vector2& screenPos_, const Vector2& scale_, const float rotAngle_, const Color& tintColor_)
{
	spriteTexture = &spriteTexture_;

	setHudTransform(pivot_, screenPos_, scale_, rotAngle_);
	setTintColor(tintColor_);
}

void SpriteRendererComponent::setSpriteTexture(const Texture& spriteTexture_)
{
	spriteTexture = &spriteTexture_;
}

const Texture& SpriteRendererComponent::getSpriteTexture() const
{
	return *spriteTexture;
}

Vector2 SpriteRendererComponent::getSize() const
{
	if (!spriteTexture) return getScale();

	return spriteTexture->getTextureSize() * getScale();
}

bool SpriteRendererComponent::canDraw() const
{
	return spriteTexture && getEnabled();
}

bool SpriteRendererComponent::needToComputeMatrix() const
{
	return true;
}
