#pragma once
#include <Rendering/texture.h>

class AssetTexture
{
public:
	/**
	* Load a texture from file using stbi.
	*/
	static Texture LoadTexture(const std::string texturePath, bool flipVertical = false);
};

