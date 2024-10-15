#include "assetMaterial.h"

Shader AssetMaterial::LoadShaderProgram(const std::string vertexName, const std::string fragmentName, ShaderType shaderType)
{
	Shader shader;
	//shader.load(vertexName, fragmentName, shaderType);
	return shader;
}

Material AssetMaterial::LoadMaterial(Shader* shaderUsed)
{
	Material material;
	material.load(shaderUsed);
	return material;
}
