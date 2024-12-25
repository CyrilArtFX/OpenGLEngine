#pragma once
#include <string>


//  define anisotropic filtering since it's not defined in glad
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF


class Texture
{
public:
	Texture();
	Texture(const std::string& texturePath, const bool flipVertical);
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	void use() const; //  use (bind) the texture

	void setWrappingParameters(unsigned int sAxis, unsigned int tAxis);
	void setFilteringParameters(unsigned int minifying, unsigned int magnifying);

	unsigned int getTextureID() const { return ID; }

	int getTextureWidth() const { return width; }
	int getTextureHeight() const { return height; }
	struct Vector2Int getTextureSize() const;

private:
	unsigned int ID{ 0 }; //  texture ID

	int width{ 0 };
	int height{ 0 };

	void load(const std::string& texturePath, bool flipVertical);
	unsigned int getGlFormat(const int nbChannels);
};

