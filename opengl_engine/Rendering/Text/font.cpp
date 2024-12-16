#include "font.h"

#include <ft2build.h>
#include <freetype/freetype.h>
#include <glad/glad.h>

#include <ServiceLocator/locator.h>
#include <Utils/defines.h>


Font::Font() : FontSize(0)
{
}

Font::Font(const std::string& fontPath, const int size, const CharacterLoading charLoadSetting) : FontSize(size)
{
	std::string font_path = RESOURCES_PATH + fontPath;

	//  initialize freetype
	FT_Error error;
	FT_Library ft;
	error = FT_Init_FreeType(&ft);
	if (error)
	{
		Locator::getLog().LogMessage_Category("Font: Failed to initialize FreeType library.", LogCategory::Error);
		return;
	}

	FT_Face face;
	error = FT_New_Face(ft, font_path.c_str(), 0, &face);
	if (error)
	{
		Locator::getLog().LogMessage_Category("Font: Failed to load font at path " + font_path + ".", LogCategory::Error);
		return;
	}

	//  set size to load glyph
	FT_Set_Pixel_Sizes(face, FontSize, FontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	//  convert char load setting
	int char_count;
	switch (charLoadSetting)
	{
	case CharacterLoading::ASCII_128:
		char_count = 128;
		break;

	default:
		char_count = 128; //  make ascii 128 if unknown setting
		break;
	}

	//  generate the array of texture
	glGenTextures(1, &CharTextureArray);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, CharTextureArray);

	//  setup the texture 3D (this is the array of textures), here the FontSize are for the size of the textures and the char_count for the size of the array
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_R8, FontSize, FontSize, char_count, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

	//  load characters
	for (unsigned char c = 0; c < char_count; c++)
	{
		//  load character glyph
		error = FT_Load_Char(face, c, FT_LOAD_RENDER);
		if (error)
		{
			Locator::getLog().LogMessage_Category("Font: Failed to load character glyph at char '" + std::string(1, c) + "'.", LogCategory::Error);
			continue;
		}

		//  add a texture into the texture 3D (the array of texture)
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY,
			0,
			0, 0, //  offset x & y
			int(c), //  offset z (the index to set the texture in the array)
			face->glyph->bitmap.width, //  size width
			face->glyph->bitmap.rows, //  size height
			1, //  size depth (leave at 1)
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer //  datas of the texture
		);

		//  set texture options
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//  store character for later use
		FontCharacters.emplace(c,
			FontCharacter{
				int(c), //  index of the texture in the texture 3D (array)
				Vector2Int{ (int)(face->glyph->bitmap.width), (int)(face->glyph->bitmap.rows) },
				Vector2Int{ face->glyph->bitmap_left, face->glyph->bitmap_top },
				face->glyph->advance.x
			}
		);
	}

	//  unbind texture
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	//  release freetype
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}


void Font::use() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, CharTextureArray);
}

const int Font::getFontSize() const
{
	return FontSize;
}

const FontCharacter& Font::getCharacter(const char& c) const
{
	if (c >= FontCharacters.size())
	{
		Locator::getLog().LogMessage_Category("Font: Tried to get a character outside of the char range loaded on this font.", LogCategory::Warning);
		return FontCharacter::errorChar;
	}

	return FontCharacters.at(c);
}
