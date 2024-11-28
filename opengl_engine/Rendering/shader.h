#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

enum class ShaderType : uint8_t
{
	Null,
	Lit,
	Unlit
};

class Shader
{
public:
	Shader();
	Shader(const std::string& vertexName, const std::string& fragmentName, const ShaderType shaderType);
	~Shader();

	void use(); //  use (activate) the shader
	void deleteProgram();

	//  setter uniform fonctions
	void setBool(const std::string& name, const bool value) const;
	void setInt(const std::string& name, const int value) const;
	void setFloat(const std::string& name, const float value) const;
	void setVec2(const std::string& name, const class Vector2& value) const;
	void setVec2(const std::string& name, const float xValue, const float yValue) const;
	void setVec3(const std::string& name, const class Vector3& value) const;
	void setVec3(const std::string& name, const float xValue, const float yValue, const float zValue) const;
	void setVec4(const std::string& name, const class Vector4& value) const;
	void setVec4(const std::string& name, const float xValue, const float yValue, const float zValue, const float wValue) const;

	void setBoolArray(const std::string& name, const bool* firstValue, const int arraySize) const;
	void setIntArray(const std::string& name, const int* firstValue, const int arraySize) const;
	void setFloatArray(const std::string& name, const float* firstValue, const int arraySize) const;
	void setVec2Array(const std::string& name, const class Vector2* firstValue, const int arraySize) const;
	void setVec3Array(const std::string& name, const class Vector3* firstValue, const int arraySize) const;
	void setVec4Array(const std::string& name, const class Vector4* firstValue, const int arraySize) const;

	void setMatrix4(const std::string& name, const float* value) const;
	void setMatrix4Array(const std::string& name, const float* firstValue, const int arraySize) const;

	unsigned int getProgram() const { return ID; }

	ShaderType getShaderType() const { return type; }

	bool isLoaded() const { return loaded; }

private:
	bool loaded{ false };

	unsigned int ID{ 0 }; //  program ID

	ShaderType type{ ShaderType::Null };


	//  reads and builds the shader program
	void load(const std::string& vertexName, const std::string& fragmentName, const ShaderType shaderType);
};