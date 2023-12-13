#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

enum ShaderType
{
	Null,
	Lit,
	Unlit
};

class Shader
{
public:
	Shader();
	//  reads and builds the shader program
	void load(const std::string vertexName, const std::string fragmentName, ShaderType shaderType);

	void use(); //  use (activate) the shader
	void deleteProgram();

	//  setter uniform fonctions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, class Vector3 value) const;
	void setVec3(const std::string& name, float xValue, float yValue, float zValue) const;
	void setMatrix4(const std::string& name, const float* value) const;

	unsigned int getProgram() { return ID; }

	ShaderType getShaderType() { return type; }

	bool isLoaded() const { return loaded; }

private:
	bool loaded = false;

	unsigned int ID = 0; //  program ID

	ShaderType type = ShaderType::Null;
};