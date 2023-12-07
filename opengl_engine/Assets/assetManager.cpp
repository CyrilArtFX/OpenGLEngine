#include "assetManager.h"
#include <iostream>


std::unordered_map<std::string, Mesh> AssetManager::meshesSingle;
std::unordered_map<std::string, MeshCollection> AssetManager::meshesCollection;


void AssetManager::LoadSingleMesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	if (meshesSingle.find(name) != meshesSingle.end())
	{
		std::cout << "Asset Manager Error: Tried to load a single mesh with a name that already exists.\n";
		return;
	}

	meshesSingle[name] = AssetMesh::LoadSingleMesh(vertices, indices);
}

void AssetManager::LoadSingleMesh(std::string name, std::string filepath)
{
	if (meshesSingle.find(name) != meshesSingle.end())
	{
		std::cout << "Asset Manager Error: Tried to load a single mesh with a name that already exists.\n";
		return;
	}
}

void AssetManager::LoadMeshCollection(std::string name, std::string filepath)
{
	if (meshesCollection.find(name) != meshesCollection.end())
	{
		std::cout << "Asset Manager Error: Tried to load a mesh collection with a name that already exists.\n";
		return;
	}
}

Mesh& AssetManager::GetSingleMesh(std::string name)
{
	if (meshesSingle.find(name) == meshesSingle.end())
	{
		std::cout << "Asset Manager Error: Tried to get a single mesh with a name that doesn't exists.\n";
		Mesh null_mesh;
		return null_mesh;
	}

	return meshesSingle[name];
}

MeshCollection& AssetManager::GetMeshCollection(std::string name)
{
	if (meshesCollection.find(name) == meshesCollection.end())
	{
		std::cout << "Asset Manager Error: Tried to get a mesh collection with a name that doesn't exists.\n";
		MeshCollection null_collection{};
		return null_collection;
	}

	return meshesCollection[name];
}





void AssetManager::DeleteObjects()
{
	for (auto collection : meshesCollection) 
	{
		for (auto mesh : collection.second.collection) 
		{
			mesh.deleteObjects(); 
		}
	}

	for (auto mesh : meshesSingle) 
	{
		mesh.second.deleteObjects();
	}
}