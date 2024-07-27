#include "assetTexture.h"

Texture AssetTexture::LoadTexture(const std::string texturePath, bool flipVertical)
{
	Texture texture;
	texture.load(texturePath, flipVertical);
	return texture;
}
