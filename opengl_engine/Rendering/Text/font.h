#pragma once
#include <map>
#include <Rendering/Text/textRenderUtils.h>

class Font
{
public:
	Font();
	Font(const std::string& fontPath, const int size, const CharacterLoading charLoadSetting);
	Font(const Font&) = delete;
	Font& operator=(const Font&) = delete;

	void use() const;
	const int getFontSize() const;
	const FontCharacter& getCharacter(const char& c) const;


private:
	unsigned int FontSize;
	std::map<char, FontCharacter> FontCharacters;
	unsigned int CharTextureArray{ 0 };
};

