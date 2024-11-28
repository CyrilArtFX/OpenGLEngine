#pragma once
#include <Rendering/Hud/hudComponent.h>
#include <string>

class Font;


/** Text Renderer Component
*/
class TextRendererComponent : public HudComponent
{
public:
	TextRendererComponent();
	TextRendererComponent(const TextRendererComponent& other);
	~TextRendererComponent();
	TextRendererComponent& operator=(const TextRendererComponent& other) = delete;

	void setTextDatas(const std::string& text_, const Font& textFont_, const Vector2& pivot_, const Vector2& screenPos_, const Vector2& scale_, const float rotAngle_, const Color& tintColor_);

	void setText(const std::string& text_);
	const std::string& getText() const;

	void setTextFont(const Font& textFont_);
	const Font& getTextFont() const;

	const Vector2& getRawTextSize() const;

	Vector2 getSize() const override;

protected:
	bool needToComputeMatrix() const override;

private:
	std::string text;
	const Font* textFont;
	Vector2 textSize;

	void recomputeTextSize();
	void computeTextLineSize(std::string textLine, int& textWidth, int& textHeight);
};