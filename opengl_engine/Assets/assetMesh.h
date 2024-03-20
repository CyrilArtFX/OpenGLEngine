#pragma once
#include <Rendering/Model/mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>


class AssetMesh
{
public:
	/**
	* Load a single mesh from handcoded vertices. 
	*/
	static Mesh LoadSingleMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices = {});

	/**
	* Load a single mesh from a 3D file using assimp.
	* WARNING : It will load only the root mesh.
	*/
	static Mesh LoadSingleMesh(std::string filepath);

	/**
	* Load an entire model from a 3D file using assimp.
	* Will return the meshes in a vector.
	*/
	static MeshCollection LoadMeshCollection(std::string filepath);

private:
	static Mesh processNodeSingle(aiNode* node, const aiScene* scene);
	static void processNodeCollection(aiNode* node, const aiScene* scene, MeshCollection& meshCollection);
	static Mesh processMesh(aiMesh* mesh, aiNode* node, const aiScene* scene);
	static aiMatrix4x4 retrieveParentTransform(aiNode* node);
};