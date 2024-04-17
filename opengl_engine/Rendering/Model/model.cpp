#include "model.h"

Model::Model()
{
}

void Model::draw(Material* materialInUsage)
{
	//  assume the shader is already in use (the rendering process should have done it)

	for (auto mesh_material : meshMaterials)
	{
		if (mesh_material.material != materialInUsage) continue;

		mesh_material.mesh->draw();
	}
}


void Model::addMesh(Mesh* mesh, Material* material)
{
	meshMaterials.push_back(MeshMaterial{ mesh, material });
}

void Model::addMeshes(MeshCollection* meshes, Material* material)
{
	for (int i = 0; i < meshes->collection.size(); i++)
	{
		meshMaterials.push_back(MeshMaterial{ &meshes->collection[i], material });
	}
}

void Model::changeMaterial(int index, Material* newMaterial)
{
	if (index < 0 || index >= meshMaterials.size()) return;
	meshMaterials[index].material = newMaterial;
}
