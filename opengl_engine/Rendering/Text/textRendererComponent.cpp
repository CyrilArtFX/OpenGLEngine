#include "textRendererComponent.h"
#include <Assets/assetManager.h>
#include <Rendering/Text/font.h>

#include <ServiceLocator/locator.h>
#include <ServiceLocator/renderer.h>


TextRendererComponent::TextRendererComponent() :
	text(""), textColor(Color::white), textScreenPosition(Vector2::zero), textScale(1.0f), textFont(&AssetManager::GetFont("arial_64"))
{
	Locator::getRenderer().AddText(this);
}

TextRendererComponent::TextRendererComponent(const TextRendererComponent& other) :
	text(other.text), textColor(other.textColor), textScreenPosition(other.textScreenPosition), textScale(other.textScale), textFont(other.textFont)
{
	Locator::getRenderer().AddText(this);
}

TextRendererComponent::~TextRendererComponent()
{
	Locator::getRenderer().RemoveText(this);
}



void TextRendererComponent::setTextDatas(const std::string& newText, const Color& newTextColor, const Vector2& newTextScreenPosition, const float newTextScale, const Font& newTextFont)
{
	text = newText;
	textColor = newTextColor;
	textScreenPosition = newTextScreenPosition;
	textScale = newTextScale;
	textFont = &newTextFont;
}

void TextRendererComponent::setText(const std::string& newText)
{
	text = newText;
}

void TextRendererComponent::setTextColor(const Color& newTextColor)
{
	textColor = newTextColor;
}

void TextRendererComponent::setTextScreenPosition(const Vector2& newTextScreenPosition)
{
	textScreenPosition = newTextScreenPosition;
}

void TextRendererComponent::setTextScale(const float newTextScale)
{
	textScale = newTextScale;
}

void TextRendererComponent::setTextFont(const Font& newTextFont)
{
	textFont = &newTextFont;
}

const std::string& TextRendererComponent::getText() const
{
	return text;
}

const Color& TextRendererComponent::getTextColor() const
{
	return textColor;
}

const Vector2& TextRendererComponent::getTextScreenPosition() const
{
	return textScreenPosition;
}

const float TextRendererComponent::getTextScale() const
{
	return textScale;
}

const Font& TextRendererComponent::getTextFont() const
{
	return *textFont;
}

void TextRendererComponent::setEnable(const bool enable)
{
	enabled = enable;
}

bool TextRendererComponent::isEnabled() const
{
	return enabled;
}
