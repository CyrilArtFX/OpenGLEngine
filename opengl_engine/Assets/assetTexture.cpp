#include "assetTexture.h"

Texture AssetTexture::LoadTexture(const std::string texturePath, unsigned int glFormat, bool flipVertical)
{
	Texture texture;
	texture.load(texturePath, glFormat, flipVertical);
	return texture;
}
