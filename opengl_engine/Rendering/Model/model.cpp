#include "model.h"

Model::Model()
{
}

void Model::draw(std::shared_ptr<Material> materialInUsage)
{
	//  assume the shader is already in use (the rendering process should have done it)

	for (auto mesh_material : meshMaterials)
	{
		if (mesh_material.first != materialInUsage) continue;

		for (auto mesh : mesh_material.second)
		{
			mesh->draw();
		}
	}
}


void Model::addMesh(Mesh* mesh, std::shared_ptr<Material> material)
{
	meshMaterials[material].push_back(mesh);
}

void Model::addMeshes(MeshCollection* meshes, std::shared_ptr<Material> material)
{
	for (int i = 0; i < meshes->collection.size(); i++)
	{
		meshMaterials[material].push_back(&meshes->collection[i]);
	}
}
