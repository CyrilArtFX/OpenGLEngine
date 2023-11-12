#pragma once

#include "shader.h"

enum MaterialType
{
	Lit,
	Unlit
};

class Material
{
public:
	Material(Shader& shaderUsed, MaterialType matType_) : shader(shaderUsed), matType(matType_) {}
	virtual ~Material() {}

	virtual void use() = 0;

	Shader& getShader() { return shader; }
	MaterialType getMatType() { return matType; }

protected:
	Shader& shader;

private:
	MaterialType matType;
};