#pragma once

#include <glad/glad.h>

#include <stb_image.h>

#include <iostream>

class Texture
{
public:
	Texture(const char* texturePath, unsigned int glFormat, bool flipVertical); //  constructor builds texture

	void use(); //  use (bind) the texture

	void setWrappingParameters(unsigned int sAxis, unsigned int tAxis);
	void setFilteringParameters(unsigned int minifying, unsigned int magnifying);

	unsigned int getTextureID() { return ID; }

private:
	unsigned int ID; //  texture ID
};

