#include "texture.h"
#include <Utils/defines.h>

Texture::Texture()
{
}

void Texture::load(const std::string texturePath, unsigned int glFormat, bool flipVertical)
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


	int width, height, nr_channels;
	stbi_set_flip_vertically_on_load(flipVertical);
	unsigned char* data = stbi_load(tex_path.c_str(), &width, &height, &nr_channels, 0);

	if (data)
	{
		//  be careful to not load with GL_RGBA if color depth is 24 (even with png)
		glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, data);
		//  in some cases, the glGenerateMipmap function can cause crashes (it's related to the size of the image, but I don't know exactly what causes this problem)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture at path " << tex_path << std::endl;

		stbi_set_flip_vertically_on_load(false);
		std::string notex_path = RESOURCES_PATH + "Default/notexture.png";
		data = stbi_load(notex_path.c_str(), &width, &height, &nr_channels, 0);

		if (!data) std::cout << "WARNING !  Default texture notexture not found !\n"; //  I choose to not prevent the crash
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(data);

	loaded = true;
}


void Texture::use()
{
	if (!loaded) return;

	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::setWrappingParameters(unsigned int sAxis, unsigned int tAxis)
{
	if (!loaded) return;

	use();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sAxis);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tAxis);
}

void Texture::setFilteringParameters(unsigned int minifying, unsigned int magnifying)
{
	if (!loaded) return;

	use();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minifying);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnifying);
}
