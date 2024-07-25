#include "assetManager.h"
#include <iostream>


std::unordered_map<std::string, Texture> AssetManager::textures;
std::unordered_map<std::string, Mesh> AssetManager::meshesSingle;
std::unordered_map<std::string, MeshCollection> AssetManager::meshesCollection;
std::unordered_map<std::string, Model> AssetManager::models;
std::unordered_map<std::string, Shader> AssetManager::shaders;
std::unordered_map<std::string, Material> AssetManager::materials;
std::unordered_map<std::string, MaterialCollection> AssetManager::materialsCollection;


void AssetManager::LoadTexture(std::string name, const std::string texturePath, unsigned int glFormat, bool flipVertical)
{
	if (textures.find(name) != textures.end())
	{
		std::cout << "Asset Manager Error: Tried to load a texture with a name that already exists. Name is " << name << ".\n";
		return;
	}
	
	textures.emplace(name, AssetTexture::LoadTexture(texturePath, glFormat, flipVertical));
}

Texture& AssetManager::GetTexture(std::string name)
{
	if (textures.find(name) == textures.end())
	{
		std::cout << "Asset Manager Error: Tried to get a texture with a name that doesn't exists. Name is " << name << ".\n";
		return textures["null_texture"];
	}

	return textures[name];
}

void AssetManager::DeleteTexture(std::string name)
{
	if (textures.find(name) == textures.end())
	{
		std::cout << "Asset Manager Error: Tried to delete a texture with a name that doesn't exists. Name is " << name << ".\n";
		return;
	}

	textures.erase(name);
}


void AssetManager::LoadSingleMesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	if (meshesSingle.find(name) != meshesSingle.end())
	{
		std::cout << "Asset Manager Error: Tried to load a single mesh with a name that already exists. Name is " << name << ".\n";
		return;
	}

	meshesSingle.emplace(name, AssetMesh::LoadSingleMesh(vertices, indices));
}

void AssetManager::LoadSingleMesh(std::string name, std::string filepath)
{
	if (meshesSingle.find(name) != meshesSingle.end())
	{
		std::cout << "Asset Manager Error: Tried to load a single mesh with a name that already exists. Name is " << name << ".\n";
		return;
	}

	meshesSingle.emplace(name, AssetMesh::LoadSingleMesh(filepath));
}

void AssetManager::LoadMeshCollection(std::string name, std::string filepath)
{
	if (meshesCollection.find(name) != meshesCollection.end())
	{
		std::cout << "Asset Manager Error: Tried to load a mesh collection with a name that already exists. Name is " << name << ".\n";
		return;
	}

	meshesCollection.emplace(name, AssetMesh::LoadMeshCollection(filepath));
}

Mesh& AssetManager::GetSingleMesh(std::string name)
{
	if (meshesSingle.find(name) == meshesSingle.end())
	{
		std::cout << "Asset Manager Error: Tried to get a single mesh with a name that doesn't exists. Name is " << name << ".\n";
		return meshesSingle["null_mesh"];
	}

	return meshesSingle[name];
}

MeshCollection& AssetManager::GetMeshCollection(std::string name)
{
	if (meshesCollection.find(name) == meshesCollection.end())
	{
		std::cout << "Asset Manager Error: Tried to get a mesh collection with a name that doesn't exists. Name is " << name << ".\n";
		return meshesCollection["null_collection"];
	}

	return meshesCollection[name];
}

void AssetManager::DeleteSingleMesh(std::string name)
{
	if (meshesSingle.find(name) == meshesSingle.end())
	{
		std::cout << "Asset Manager Error: Tried to delete a single mesh with a name that doesn't exists. Name is " << name << ".\n";
		return;
	}

	meshesSingle[name].deleteObjects();
	meshesSingle.erase(name);
}

void AssetManager::DeleteMeshCollection(std::string name)
{
	if (meshesCollection.find(name) == meshesCollection.end())
	{
		std::cout << "Asset Manager Error: Tried to delete a mesh collection with a name that doesn't exists. Name is " << name << ".\n";
		return;
	}

	for (auto& mesh : meshesCollection[name].collection)
	{
		mesh.deleteObjects();
	}
	meshesCollection.erase(name);
}


Model& AssetManager::CreateModel(std::string name)
{
	if (models.find(name) != models.end())
	{
		std::cout << "Asset Manager Error: Tried to create a model with a name that already exists. Name is " << name << ".\n";
		return models["null_model"];
	}

	models.emplace(name, Model());
	return models[name];
}

Model& AssetManager::GetModel(std::string name)
{
	if (models.find(name) == models.end())
	{
		std::cout << "Asset Manager Error: Tried to get a model with a name that doesn't exists. Name is " << name << ".\n";
		return models["null_model"];
	}

	return models[name];
}

void AssetManager::DeleteModel(std::string name)
{
	if (models.find(name) == models.end())
	{
		std::cout << "Asset Manager Error: Tried to delete a model with a name that doesn't exists. Name is " << name << ".\n";
		return;
	}

	models.erase(name);
}

void AssetManager::CreateShaderProgram(std::string name, const std::string vertexName, const std::string fragmentName, ShaderType shaderType)
{
	if (shaders.find(name) != shaders.end())
	{
		std::cout << "Asset Manager Error: Tried to create a shader with a name that already exists. Name is " << name << ".\n";
		return;
	}

	shaders.emplace(name, AssetMaterial::LoadShaderProgram(vertexName, fragmentName, shaderType));
}

Shader& AssetManager::GetShader(std::string name)
{
	if (shaders.find(name) == shaders.end())
	{
		std::cout << "Asset Manager Error: Tried to get a shader with a name that doesn't exists. Name is " << name << ".\n";
		return shaders["null_shader"];
	}

	return shaders[name];
}

void AssetManager::DeleteShader(std::string name)
{
	if (shaders.find(name) == shaders.end())
	{
		std::cout << "Asset Manager Error: Tried to delete a shader with a name that doesn't exists. Name is " << name << ".\n";
		return;
	}

	shaders[name].deleteProgram();
	shaders.erase(name);
}

Material& AssetManager::CreateMaterial(std::string name, Shader* shaderUsed)
{
	if (materials.find(name) != materials.end())
	{
		std::cout << "Asset Manager Error: Tried to create a material with a name that already exists. Name is " << name << ".\n";
		return materials["null_material"];
	}

	materials.emplace(name, AssetMaterial::LoadMaterial(shaderUsed));
	return materials[name];
}

MaterialCollection& AssetManager::CreateMaterialCollection(std::string name, MaterialCollection materialCollection)
{
	if (materialsCollection.find(name) != materialsCollection.end())
	{
		std::cout << "Asset Manager Error: Tried to create a material collection with a name that already exists. Name is " << name << ".\n";
		return materialsCollection["null_mat_collection"];
	}

	materialsCollection.emplace(name, materialCollection);
	return materialsCollection[name];
}

Material& AssetManager::GetMaterial(std::string name)
{
	if (materials.find(name) == materials.end())
	{
		std::cout << "Asset Manager Error: Tried to get a material with a name that doesn't exists. Name is " << name << ".\n";
		return materials["null_material"];
	}

	return materials[name];
}

MaterialCollection& AssetManager::GetMaterialCollection(std::string name)
{
	if (materialsCollection.find(name) == materialsCollection.end())
	{
		std::cout << "Asset Manager Error: Tried to get a material collection with a name that doesn't exists. Name is " << name << ".\n";
		return materialsCollection["null_mat_collection"];
	}

	return materialsCollection[name];
}

void AssetManager::DeleteMaterial(std::string name)
{
	if (materials.find(name) == materials.end())
	{
		std::cout << "Asset Manager Error: Tried to delete a material with a name that doesn't exists. Name is " << name << ".\n";
		return;
	}

	materials.erase(name);
}





void AssetManager::DeleteObjects()
{
	for (auto& collection : meshesCollection) 
	{
		for (auto& mesh : collection.second.collection) 
		{
			mesh.deleteObjects(); 
		}
	}

	for (auto& mesh : meshesSingle) 
	{
		mesh.second.deleteObjects();
	}

	for (auto shader : shaders)
	{
		shader.second.deleteProgram();
	}
}

void AssetManager::LoadNullAssets()
{
	LoadTexture("null_texture", "Default/notexture.png", GL_RGBA, false);
	meshesSingle.emplace("null_mesh", Mesh());
	meshesCollection.emplace("null_collection", MeshCollection{});
	models.emplace("null_model", Model());
	shaders.emplace("null_shader", Shader());
	materials.emplace("null_material", Material());
	materialsCollection.emplace("null_mat_collection", MaterialCollection{});
}
