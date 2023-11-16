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
	Material(std::weak_ptr<Shader>shaderUsed, MaterialType matType_) : shader(shaderUsed.lock()), matType(matType_) {}
	virtual ~Material() {}

	virtual void use() = 0;

	Shader& getShader() { return *shader; }
	MaterialType getMatType() { return matType; }

protected:
	std::shared_ptr<Shader> shader;

private:
	MaterialType matType;
};