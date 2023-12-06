#pragma once

#include "shader.h"
#include "texture.h"

#include <vector>
#include <unordered_map>
#include <string>


class Material
{
public:
	Material(std::weak_ptr<Shader>shaderUsed);

	void use();

	void addTexture(std::weak_ptr<Texture> texture);

	Shader& getShader() { return *shader; }
	std::shared_ptr<Shader> getShrdShader() { return shader; }

protected:
	std::shared_ptr<Shader> shader;
	std::vector<std::shared_ptr<Texture>> textures = {};

	//  todo a unordered map per parameter type (int, Vector3, etc.) and a 'AddParameter()' function per parameter type too
};