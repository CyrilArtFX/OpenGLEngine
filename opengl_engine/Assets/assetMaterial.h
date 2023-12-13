#pragma once
#include <Rendering/shader.h>
#include <Rendering/material.h>

class AssetMaterial
{
public:
	/**
	* Load a shader program with shader files.
	*/
	static Shader LoadShaderProgram(const std::string vertexName, const std::string fragmentName, ShaderType shaderType);

	/**
	* Load a material with a shader.
	*/
	static Material LoadMaterial(Shader* shaderUsed);
};

