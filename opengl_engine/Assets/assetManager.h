#pragma once
#include "assetMesh.h"
#include "assetTexture.h"

#include <unordered_map>
#include <string>


class AssetManager
{
public:
	/**
	* Delete all necessary objects.
	*/
	static void DeleteObjects();


	/**
	* Load a single mesh from handcoded vertices.
	* Name = the name you want to give to this mesh in the asset storage.
	*/
	static void LoadSingleMesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices = {});

	/**
	* Load a single mesh from a 3D file using assimp.
	* WARNING : It will load only the root mesh.
	* Name = the name you want to give to this mesh in the asset storage.
	*/
	static void LoadSingleMesh(std::string name, std::string filepath);

	/**
	* Load an entire model from a 3D file using assimp.
	* Will put the meshes in a vector.
	* Name = the name you want to give to this mesh in the asset storage.
	*/
	static void LoadMeshCollection(std::string name, std::string filepath);

	/**
	* Retrieve a single mesh from the asset storage.
	*/
	static Mesh& GetSingleMesh(std::string name);

	/**
	* Retrieve a collection of mesh from the asset storage.
	*/
	static MeshCollection& GetMeshCollection(std::string name);


private:
	static std::unordered_map<std::string, Mesh> meshesSingle;
	static std::unordered_map<std::string, MeshCollection> meshesCollection;
};

