#include "assetTexture.h"

Texture AssetTexture::LoadTexture(const std::string texturePath, TextureType textureType, unsigned int glFormat, bool flipVertical)
{
	Texture texture;
	texture.load(texturePath, textureType, glFormat, flipVertical);
	return texture;
}
