#pragma once
#include <Rendering/Model/mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>


struct LoadMeshData
{
	std::vector<Vertex> vertices{};
	std::vector<unsigned int> indices{};
	int matId{ 0 };
};


class AssetMesh
{
public:
	/**
	* Load a single mesh from a 3D file using assimp.
	* WARNING : It will load only the root mesh.
	*/
	static LoadMeshData LoadSingleMesh(std::string filepath);

	/**
	* Load an entire model from a 3D file using assimp.
	* Will return the meshes in a vector.
	*/
	static std::vector<LoadMeshData> LoadMeshCollection(std::string filepath);

private:
	static LoadMeshData processNodeSingle(aiNode* node, const aiScene* scene);
	static void processNodeCollection(aiNode* node, const aiScene* scene, std::vector<LoadMeshData>& meshCollection);
	static LoadMeshData processMesh(aiMesh* mesh, aiNode* node, const aiScene* scene);
	static aiMatrix4x4 retrieveParentTransform(aiNode* node);
};