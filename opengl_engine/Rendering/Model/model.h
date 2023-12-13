#pragma once
#include "mesh.h"
#include <Rendering/material.h>

#include <unordered_map>
#include <vector>


class Model
{
public:
	Model();

	void draw(Material* materialInUsage);

	/**
	* Add a single mesh to a model with a material.
	*/
	void addMesh(Mesh* mesh, Material* material);

	/**
	* Add a collection of mesh to a model with the same material for all.
	*/
	void addMeshes(MeshCollection* meshes, Material* material);

private:
	std::unordered_map<Material*, std::vector<Mesh*>> meshMaterials;
};

