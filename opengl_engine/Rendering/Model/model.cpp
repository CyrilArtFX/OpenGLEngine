#include "model.h"
#include <Assets/assetManager.h>

Model::Model()
{
}

void Model::draw(Material* materialInUsage)
{
	//  assume the shader is already in use (the rendering process should have done it)

	for (auto& mesh_material : meshMaterials)
	{
		if (mesh_material.material != materialInUsage) continue;

		mesh_material.mesh.draw();
	}
}


void Model::addMesh(Mesh& mesh, Material* material)
{
	meshMaterials.push_back(MeshMaterial{ mesh, material });
}

void Model::addMeshes(MeshCollection& meshes, MaterialCollection* materials)
{
	for (int i = 0; i < meshes.collection.size(); i++)
	{
		int mesh_mat_id = meshes.collection[i]->getMaterialIndex();
		if (mesh_mat_id < materials->collection.size()) // mesh material ID exist in the material collection
		{
			meshMaterials.push_back(MeshMaterial{ *meshes.collection[i], materials->collection[mesh_mat_id] });
		}
		else
		{
			meshMaterials.push_back(MeshMaterial{ *meshes.collection[i], &AssetManager::GetMaterial("null_material") });
		}
	}
}

void Model::addMeshes(MeshCollection& meshes, Material* material)
{
	for (int i = 0; i < meshes.collection.size(); i++)
	{
		meshMaterials.push_back(MeshMaterial{ *meshes.collection[i], material });
	}
}

void Model::changeMaterial(int materialId, Material* newMaterial)
{
	for (int i = 0; i < meshMaterials.size(); i++)
	{
		if (meshMaterials[i].mesh.getMaterialIndex() == materialId)
		{
			meshMaterials[i].material = newMaterial;
		}
	}
}
