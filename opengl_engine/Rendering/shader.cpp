#include "shader.h"

#include <Maths/vector3.h>

Shader::Shader(const std::string vertexName, const std::string fragmentName, ShaderType shaderType) : type(shaderType)
{
	//  Step 1 : retrieve the shaders source code from filePaths
	//  ========================================================

	std::string vertex_path = shaderPath + vertexName;
	std::string fragment_path = shaderPath + fragmentName;


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
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
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
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	} //  check if vertex shader has correctly compiled

	//  fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &f_shader_code, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
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
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	} //  check if shader program correctly linked shaders

	//  delete shaders once they're link into the program
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


void Shader::use()
{
	glUseProgram(ID);
}

void Shader::deleteProgram()
{
	glDeleteProgram(ID);
}


void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, Vector3 value) const
{
	setVec3(name, value.x, value.y, value.z);
}

void Shader::setVec3(const std::string& name, float xValue, float yValue, float zValue) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), xValue, yValue, zValue);
}

void Shader::setMatrix4(const std::string& name, const float* value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value);
}
