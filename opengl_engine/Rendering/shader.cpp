#include "shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>

#include <Maths/vector2.h>
#include <Maths/vector3.h>
#include <Maths/vector4.h>
#include <Utils/defines.h>

#include <ServiceLocator/locator.h>


Shader::Shader()
{
	//  default constructor will create a unloaded shader that will be unable to do anything
}

Shader::Shader(const std::string& vertexName, const std::string& fragmentName, const ShaderType shaderType)
{
	load(vertexName, fragmentName, shaderType);
}

Shader::~Shader()
{
	deleteProgram();
}

void Shader::load(const std::string& vertexName, const std::string& fragmentName, const ShaderType shaderType)
{
	type = shaderType;

	//  Step 1 : retrieve the shaders source code from filePaths
	//  ========================================================

	const std::string vertex_path = SHADER_PATH + vertexName;
	const std::string fragment_path = SHADER_PATH + fragmentName;


	std::string vertex_code;
	std::string fragment_code;
	std::ifstream v_shader_file;
	std::ifstream f_shader_file;

	//  ensure ifstream objects can throw exceptions
	v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//  open files
		v_shader_file.open(vertex_path);
		f_shader_file.open(fragment_path);
		std::stringstream v_shader_stream, f_shader_stream;

		//  read files's buffer contents into streams
		v_shader_stream << v_shader_file.rdbuf();
		f_shader_stream << f_shader_file.rdbuf();

		//  close file handlers
		v_shader_file.close();
		f_shader_file.close();

		//  convert stream into string
		vertex_code = v_shader_stream.str();
		fragment_code = f_shader_stream.str();
	}
	catch (std::ifstream::failure e)
	{
		Locator::getLog().LogMessage_Category("Shader: Failed to read shader files.", LogCategory::Error);
	}

	const char* v_shader_code = vertex_code.c_str();
	const char* f_shader_code = fragment_code.c_str();


	//  Step 2 : compile shaders and link them into the program
	//  =======================================================

	unsigned int vertex, fragment;
	int success;
	char info_log[512];

	//  vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &v_shader_code, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, info_log);
		Locator::getLog().LogMessage_Category("Shader: Failed to compile vertex shader.", LogCategory::Error);
	} //  check if vertex shader has correctly compiled

	//  fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &f_shader_code, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, info_log);
		Locator::getLog().LogMessage_Category("Shader: Failed to compile fragment shader.", LogCategory::Error);
	} //  check if fragment shader has correctly compiled

	//  shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, info_log);
		Locator::getLog().LogMessage_Category("Shader: Failed to link shader program.", LogCategory::Error);
	} //  check if shader program correctly linked shaders

	//  delete shaders once they're link into the program
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	loaded = true;
}

void Shader::use()
{
	if (!loaded) return;

	glUseProgram(ID);
}

void Shader::deleteProgram()
{
	if (!loaded) return;

	glDeleteProgram(ID);
}


void Shader::setBool(const std::string& name, const bool value) const
{
	if (!loaded) return;

	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, const int value) const
{
	if (!loaded) return;

	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, const float value) const
{
	if (!loaded) return;

	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const Vector2& value) const
{
	//if (!loaded) return;

	setVec2(name, value.x, value.y);
}

void Shader::setVec2(const std::string& name, const float xValue, const float yValue) const
{
	if (!loaded) return;

	glUniform2f(glGetUniformLocation(ID, name.c_str()), xValue, yValue);
}

void Shader::setVec3(const std::string& name, const Vector3& value) const
{
	//if (!loaded) return;

	setVec3(name, value.x, value.y, value.z);
}

void Shader::setVec3(const std::string& name, const float xValue, const float yValue, const float zValue) const
{
	if (!loaded) return;

	glUniform3f(glGetUniformLocation(ID, name.c_str()), xValue, yValue, zValue);
}

void Shader::setVec4(const std::string& name, const Vector4& value) const
{
	//if (!loaded) return;

	setVec4(name, value.x, value.y, value.z, value.w);
}

void Shader::setVec4(const std::string& name, const float xValue, const float yValue, const float zValue, const float wValue) const
{
	if (!loaded) return;

	glUniform4f(glGetUniformLocation(ID, name.c_str()), xValue, yValue, zValue, wValue);
}

void Shader::setBoolArray(const std::string& name, const bool* firstValue, const int arraySize) const
{
	if (!loaded) return;

	glUniform1iv(glGetUniformLocation(ID, name.c_str()), arraySize, (int*)firstValue);
}

void Shader::setIntArray(const std::string& name, const int* firstValue, const int arraySize) const
{
	if (!loaded) return;

	glUniform1iv(glGetUniformLocation(ID, name.c_str()), arraySize, firstValue);
}

void Shader::setFloatArray(const std::string& name, const float* firstValue, const int arraySize) const
{
	if (!loaded) return;

	glUniform1fv(glGetUniformLocation(ID, name.c_str()), arraySize, firstValue);
}

void Shader::setVec2Array(const std::string& name, const Vector2* firstValue, const int arraySize) const
{
	if (!loaded) return;

	glUniform2fv(glGetUniformLocation(ID, name.c_str()), arraySize, firstValue->getAsFloatPtr());
}

void Shader::setVec3Array(const std::string& name, const Vector3* firstValue, const int arraySize) const
{
	if (!loaded) return;

	glUniform3fv(glGetUniformLocation(ID, name.c_str()), arraySize, firstValue->getAsFloatPtr());
}

void Shader::setVec4Array(const std::string& name, const Vector4* firstValue, const int arraySize) const
{
	if (!loaded) return;

	glUniform4fv(glGetUniformLocation(ID, name.c_str()), arraySize, firstValue->getAsFloatPtr());
}

void Shader::setMatrix4(const std::string& name, const float* value) const
{
	if (!loaded) return;

	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value);
}

void Shader::setMatrix4Array(const std::string& name, const float* firstValue, const int arraySize) const
{
	if (!loaded) return;

	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), arraySize, GL_TRUE, firstValue);
}
