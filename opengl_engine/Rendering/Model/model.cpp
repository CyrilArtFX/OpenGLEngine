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


void Model::addMesh(std::weak_ptr<Mesh> mesh, std::shared_ptr<Material> material)
{
	meshMaterials[material].push_back(mesh.lock());
}
