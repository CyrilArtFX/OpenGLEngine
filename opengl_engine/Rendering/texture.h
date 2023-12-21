#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <string>
#include <iostream>


class Texture
{
public:
	Texture();
	void load(const std::string texturePath = "Default/notexture.png", unsigned int glFormat = GL_RGBA, bool flipVertical = false);

	void use(); //  use (bind) the texture

	void setWrappingParameters(unsigned int sAxis, unsigned int tAxis);
	void setFilteringParameters(unsigned int minifying, unsigned int magnifying);

	unsigned int getTextureID() const { return ID; }

	bool isLoaded() const { return loaded; }

private:
	bool loaded = false;

	unsigned int ID = 0; //  texture ID
};

