#include "material.h"

#include <string>

Material::Material(std::weak_ptr<Shader> shaderUsed) : shader(shaderUsed.lock())
{
}

void Material::use()
{
	unsigned int diffuse_nr = 1;
	unsigned int specular_nr = 1;
	unsigned int emissive_nr = 1;
	
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); //  activate texture unit first

		std::string number;
		TextureType type = textures[i]->getTextureType();
		switch (type)
		{

		case TextureType::Diffuse:
			number = std::to_string(diffuse_nr++);
			break;

		case TextureType::Specular:
			number = std::to_string(specular_nr++);
			break;

		case TextureType::Emissive:
			number = std::to_string(emissive_nr++);
			break;

		}

		shader->setInt("material." + Texture::TypeToString(type) + number, i); //  then set the sampler to the correct texture unit
		textures[i]->use(); //  finally bind the texture
	}

	glActiveTexture(GL_TEXTURE0); //  reinitialisate the texture activation
}


void Material::addTexture(std::weak_ptr<Texture> texture)
{
	textures.push_back(texture.lock());
}
