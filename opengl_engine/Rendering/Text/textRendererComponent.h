#pragma once
#include <Utils/color.h>
#include <Maths/Vector2.h>
#include <string>

class Font;


/** Text Renderer Component
*/
class TextRendererComponent
{
public:
	TextRendererComponent();
	TextRendererComponent(const TextRendererComponent& other);
	~TextRendererComponent();
	TextRendererComponent& operator=(const TextRendererComponent& other) = delete;

	void setTextDatas(const std::string& newText, const Color& newTextColor, const Vector2& newTextScreenPosition, const float newTextScale, const Font& newTextFont);
	void setText(const std::string& newText);
	void setTextColor(const Color& newTextColor);
	void setTextScreenPosition(const Vector2& newTextScreenPosition);
	void setTextScale(const float newTextScale);
	void setTextFont(const Font& newTextFont);

	const std::string& getText() const;
	const Color& getTextColor() const;
	const Vector2& getTextScreenPosition() const;
	const float getTextScale() const;
	const Font& getTextFont() const;

	void setEnable(const bool enable);
	bool isEnabled() const;


private:
	std::string Text;
	Color TextColor;
	Vector2 TextScreenPosition;
	float TextScale;
	const Font* TextFont;

	bool Enabled{ true };
};