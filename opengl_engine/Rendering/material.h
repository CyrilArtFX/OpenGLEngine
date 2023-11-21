#pragma once

#include "shader.h"

class Material
{
public:
	Material(std::weak_ptr<Shader>shaderUsed) : shader(shaderUsed.lock()) {}
	virtual ~Material() {}

	virtual void use() = 0;

	Shader& getShader() { return *shader; }

protected:
	std::shared_ptr<Shader> shader;
};