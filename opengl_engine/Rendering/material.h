#pragma once

#include "shader.h"
#include "texture.h"
#include <Maths/Vector3.h>

#include <vector>
#include <unordered_map>
#include <string>


enum class TextureType : uint8_t
{
	Undefined = 0,
	Diffuse = 1,
	Specular = 2,
	Emissive = 3
};


class Material
{
public:
	Material(Shader& shaderUsed);
	~Material();

	Material() = delete;
	Material(const Material&) = delete;
	Material& operator=(const Material&) = delete;

	void use();

	Shader& getShader() { return shader; }
	Shader* getShaderPtr() { return &shader; } 

	void addTexture(Texture* texture, TextureType type);

	void addParameter(std::string name, bool boolParameter);
	void addParameter(std::string name, int intParameter);
	void addParameter(std::string name, float floatParameter);
	void addParameter(std::string name, Vector3 vec3Parameter);
	void addParameter(std::string name, float vec3ParameterX, float vec3ParameterY, float vec3ParameterZ);


	static std::string TypeToString(TextureType textureType);


	bool operator==(const Material& other) const;
	bool operator!=(const Material& other) const;


private:
	uint32_t uniqueID{ 0 };

	Shader& shader;
	std::unordered_map<TextureType, std::vector<Texture*>> textures;

	std::unordered_map<std::string, bool> boolParameters;
	std::unordered_map<std::string, int> intParameters;
	std::unordered_map<std::string, float> floatParameters;
	std::unordered_map<std::string, Vector3> vector3Parameters;
};


/**
* Material collections does not "possess" the materials.
* If a material from the collection is modified (by adding a parameter or a texture for exemple), all collections that include this material will be modified.
*/
struct MaterialCollection
{
	std::vector<Material*> collection{};

	MaterialCollection() {}
	MaterialCollection(std::vector<Material*> collection_) : collection(collection_) {}
	MaterialCollection(const MaterialCollection&) = delete;
	MaterialCollection& operator=(const MaterialCollection&) = delete;
};