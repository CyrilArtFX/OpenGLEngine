#include "textRendererComponent.h"
#include <Assets/assetManager.h>
#include <Rendering/Text/font.h>

#include <ServiceLocator/locator.h>
#include <ServiceLocator/renderer.h>


TextRendererComponent::TextRendererComponent() :
	Text(""), TextColor(Color::white), TextScreenPosition(Vector2::zero), TextScale(1.0f), TextFont(&AssetManager::GetFont("arial_64"))
{
	Locator::getRenderer().AddText(this);
}

TextRendererComponent::TextRendererComponent(const TextRendererComponent& other) :
	Text(other.Text), TextColor(other.TextColor), TextScreenPosition(other.TextScreenPosition), TextScale(other.TextScale), TextFont(other.TextFont)
{
	Locator::getRenderer().AddText(this);
}

TextRendererComponent::~TextRendererComponent()
{
	Locator::getRenderer().RemoveText(this);
}



void TextRendererComponent::setTextDatas(const std::string& newText, const Color& newTextColor, const Vector2& newTextScreenPosition, const float newTextScale, const Font& newTextFont)
{
	Text = newText;
	TextColor = newTextColor;
	TextScreenPosition = newTextScreenPosition;
	TextScale = newTextScale;
	TextFont = &newTextFont;
}

void TextRendererComponent::setText(const std::string& newText)
{
	Text = newText;
}

void TextRendererComponent::setTextColor(const Color& newTextColor)
{
	TextColor = newTextColor;
}

void TextRendererComponent::setTextScreenPosition(const Vector2& newTextScreenPosition)
{
	TextScreenPosition = newTextScreenPosition;
}

void TextRendererComponent::setTextScale(const float newTextScale)
{
	TextScale = newTextScale;
}

void TextRendererComponent::setTextFont(const Font& newTextFont)
{
	TextFont = &newTextFont;
}

const std::string& TextRendererComponent::getText() const
{
	return Text;
}

const Color& TextRendererComponent::getTextColor() const
{
	return TextColor;
}

const Vector2& TextRendererComponent::getTextScreenPosition() const
{
	return TextScreenPosition;
}

const float TextRendererComponent::getTextScale() const
{
	return TextScale;
}

const Font& TextRendererComponent::getTextFont() const
{
	return *TextFont;
}

void TextRendererComponent::setEnable(const bool enable)
{
	Enabled = enable;
}

bool TextRendererComponent::isEnabled() const
{
	return Enabled;
}
