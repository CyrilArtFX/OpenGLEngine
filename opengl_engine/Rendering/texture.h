#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <string>
#include <iostream>


enum class TextureType : uint8_t
{
	Undefined = 0,
	Diffuse = 1,
	Specular = 2,
	Emissive = 3
};


class Texture
{
public:
	Texture();
	void load(const std::string texturePath = "Default/notexture.png", TextureType textureType = TextureType::Undefined, unsigned int glFormat = GL_RGBA, bool flipVertical = false);

	void use(); //  use (bind) the texture

	void setWrappingParameters(unsigned int sAxis, unsigned int tAxis);
	void setFilteringParameters(unsigned int minifying, unsigned int magnifying);

	unsigned int getTextureID() const { return ID; }
	TextureType getTextureType() const { return type; }
	std::string getTextureTypeAsString() const { return TypeToString(type); }

	bool isLoaded() const { return loaded; }


	static std::string TypeToString(TextureType textureType);

private:
	bool loaded = false;

	unsigned int ID = 0; //  texture ID
	TextureType type = TextureType::Undefined;
};

