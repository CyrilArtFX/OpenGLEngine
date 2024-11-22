#pragma once
#include <Utils/color.h>
#include <Maths/Vector2.h>

class Texture;

/** Sprite Renderer Component
*/
class SpriteRendererComponent
{
public:
	SpriteRendererComponent();
	SpriteRendererComponent(const SpriteRendererComponent& other);
	~SpriteRendererComponent();
	SpriteRendererComponent& operator=(const SpriteRendererComponent& other) = delete;

	void setSpriteDatas(const Texture& newSprite, const Color& newSpriteColor, const Vector2& newSpriteScreenPosition, const Vector2& newSpriteScale);
	void setSprite(const Texture& newSprite);
	void setSpriteColor(const Color& newSpriteColor);
	void setSpriteScreenPosition(const Vector2& newSpriteScreenPosition);
	void setSpriteScale(const Vector2& newSpriteScale);

	const Texture& getSprite() const;
	const Color& getSpriteColor() const;
	const Vector2& getSpriteScreenPosition() const;
	const Vector2& getSpriteScale() const;

	void setEnable(const bool enable);
	bool getEnabled() const;

	/* Get the size of the sprite texture * the scale of this sprite component. */
    Vector2 getSpriteSize() const;

	/* Return true if enabled is true and if this component has a valid sprite texture. */
	bool getCanDraw() const;
	

private:
	const Texture* sprite;
	Color spriteColor;
	Vector2 spriteScreenPosition;
	Vector2 spriteScale;

	bool enabled{ true };
};