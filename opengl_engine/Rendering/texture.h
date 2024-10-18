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
	Texture(const std::string& texturePath, const bool flipVertical);
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	void use(); //  use (bind) the texture

	void setWrappingParameters(unsigned int sAxis, unsigned int tAxis);
	void setFilteringParameters(unsigned int minifying, unsigned int magnifying);

	unsigned int getTextureID() const { return ID; }

private:
	unsigned int ID{ 0 }; //  texture ID

	void load(const std::string& texturePath, bool flipVertical);
	unsigned int getGlFormat(const int nbChannels);
};

