#include "spriteRendererComponent.h"
#include <Rendering/texture.h>

#include <ServiceLocator/locator.h>
#include <ServiceLocator/renderer.h>

#include <Maths/Vector2Int.h>


SpriteRendererComponent::SpriteRendererComponent() :
	sprite(nullptr), spriteColor(Color::white), spriteScreenPosition(Vector2::zero), spriteScale(Vector2::one)
{
	Locator::getRenderer().AddSprite(this);
}

SpriteRendererComponent::SpriteRendererComponent(const SpriteRendererComponent& other) :
	sprite(other.sprite), spriteColor(other.spriteColor), spriteScreenPosition(other.spriteScreenPosition), spriteScale(other.spriteScale)
{
	Locator::getRenderer().AddSprite(this);
}

SpriteRendererComponent::~SpriteRendererComponent()
{
	Locator::getRenderer().RemoveSprite(this);
}



void SpriteRendererComponent::setSpriteDatas(const Texture& newSprite, const Color& newSpriteColor, const Vector2& newSpriteScreenPosition, const Vector2& newSpriteScale)
{
	sprite = &newSprite;
	spriteColor = newSpriteColor;
	spriteScreenPosition = newSpriteScreenPosition;
	spriteScale = newSpriteScale;
}

void SpriteRendererComponent::setSprite(const Texture& newSprite)
{
	sprite = &newSprite;
}

void SpriteRendererComponent::setSpriteColor(const Color& newSpriteColor)
{
	spriteColor = newSpriteColor;
}

void SpriteRendererComponent::setSpriteScreenPosition(const Vector2& newSpriteScreenPosition)
{
	spriteScreenPosition = newSpriteScreenPosition;
}

void SpriteRendererComponent::setSpriteScale(const Vector2& newSpriteScale)
{
	spriteScale = newSpriteScale;
}

const Texture& SpriteRendererComponent::getSprite() const
{
	return *sprite;
}

const Color& SpriteRendererComponent::getSpriteColor() const
{
	return spriteColor;
}

const Vector2& SpriteRendererComponent::getSpriteScreenPosition() const
{
	return spriteScreenPosition;
}

const Vector2& SpriteRendererComponent::getSpriteScale() const
{
	return spriteScale;
}

void SpriteRendererComponent::setEnable(const bool enable)
{
	enabled = enable;
}

bool SpriteRendererComponent::getEnabled() const
{
	return enabled;
}

Vector2 SpriteRendererComponent::getSpriteSize() const
{
	if (!sprite) return spriteScale;
	
	return sprite->getTextureSize() * spriteScale;
}

bool SpriteRendererComponent::getCanDraw() const
{
	return sprite && enabled;
}
