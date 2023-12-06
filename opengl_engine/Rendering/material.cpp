#include "material.h"

#include <string>

Material::Material(std::weak_ptr<Shader> shaderUsed) : shader(shaderUsed.lock())
{
}

void Material::use()
{
	//  assume the shader is already in use (the rendering process should have done it)

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

	for (auto parameter : boolParameters) shader->setBool(parameter.first, parameter.second);
	for (auto parameter : intParameters) shader->setInt(parameter.first, parameter.second);
	for (auto parameter : floatParameters) shader->setFloat(parameter.first, parameter.second);
	for (auto parameter : vector3Parameters) shader->setVec3(parameter.first, parameter.second);
}


void Material::addTexture(std::weak_ptr<Texture> texture)
{
	textures.push_back(texture.lock());
}

void Material::addParameter(std::string name, bool boolParameter)
{
	boolParameters[name] = boolParameter;
}

void Material::addParameter(std::string name, int intParameter)
{
	intParameters[name] = intParameter;
}

void Material::addParameter(std::string name, float floatParameter)
{
	floatParameters[name] = floatParameter;
}

void Material::addParameter(std::string name, Vector3 vec3Parameter)
{
	vector3Parameters[name] = vec3Parameter;
}

void Material::addParameter(std::string name, float vec3ParameterX, float vec3ParameterY, float vec3ParameterZ)
{
	vector3Parameters[name] = Vector3{ vec3ParameterX, vec3ParameterY, vec3ParameterZ };
}