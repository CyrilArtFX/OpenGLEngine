#include "assetTexture.h"

Texture assetTexture::LoadTexture(const std::string texturePath, TextureType textureType, unsigned int glFormat, bool flipVertical)
{
	Texture texture;
	texture.load(texturePath, textureType, glFormat, flipVertical);
	return texture;
}
