#include "texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Maths/Vector2Int.h>
#include <ServiceLocator/locator.h>
#include <Utils/defines.h>


Texture::Texture()
{
	load("Default/notexture.png", false);
}

Texture::Texture(const std::string& texturePath, const bool flipVertical)
{
	load(texturePath, flipVertical);
}

void Texture::load(const std::string& texturePath, bool flipVertical)
{
	std::string tex_path = RESOURCES_PATH + texturePath;

	//  create texture
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int nr_channels;
	stbi_set_flip_vertically_on_load(flipVertical);
	unsigned char* data = stbi_load(tex_path.c_str(), &width, &height, &nr_channels, 0);
	unsigned int gl_format = getGlFormat(nr_channels);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, gl_format, width, height, 0, gl_format, GL_UNSIGNED_BYTE, data);
		//  in some cases, the glGenerateMipmap function can cause crashes (it's related to the size of the image, but I don't know exactly what causes this problem)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		Locator::getLog().LogMessage_Category("Texture: Failed to load texture at path " + tex_path + ".", LogCategory::Error);

		stbi_set_flip_vertically_on_load(false);
		std::string notex_path = RESOURCES_PATH + "Default/notexture.png";
		data = stbi_load(notex_path.c_str(), &width, &height, &nr_channels, 0);

		if (!data) Locator::getLog().LogMessage_Category("Texture: Default texture 'notexture' not found!", LogCategory::Error); //  I choose to not prevent the crash
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(data);
}


void Texture::use() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::setWrappingParameters(unsigned int sAxis, unsigned int tAxis)
{
	use();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sAxis);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tAxis);
}

void Texture::setFilteringParameters(unsigned int minifying, unsigned int magnifying)
{
	use();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minifying);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnifying);
}

unsigned int Texture::getGlFormat(const int nbChannels)
{
	switch (nbChannels)
	{
	case 1:
		return GL_RGB8;

	case 2:
		return GL_RGB16;

	case 3:
		return GL_RGB;

	default:
		return GL_RGBA;
	}
}


Vector2Int Texture::getTextureSize() const
{
	return Vector2Int{ width, height };
}