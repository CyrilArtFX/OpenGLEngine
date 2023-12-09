#pragma once
#include "mesh.h"
#include <Rendering/material.h>

#include <unordered_map>
#include <vector>


class Model
{
public:
	Model();

	void draw(std::shared_ptr<Material> materialInUsage);

	/**
	* Add a single mesh to a model with a material.
	*/
	void addMesh(Mesh* mesh, std::shared_ptr<Material> material);

	/**
	* Add a collection of mesh to a model with the same material for all.
	*/
	void addMeshes(MeshCollection* meshes, std::shared_ptr<Material> material);

private:
	std::unordered_map<std::shared_ptr<Material>, std::vector<Mesh*>> meshMaterials;
};

