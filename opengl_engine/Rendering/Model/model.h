#pragma once
#include "mesh.h"
#include <Rendering/material.h>

#include <unordered_map>
#include <vector>


struct MeshMaterial
{
	Mesh& mesh;
	Material* material;
};


class Model
{
public:
	Model();
	~Model();

	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

	void draw(Material& materialInUsage);

	/**
	* Add a single mesh to a model with a material.
	*/
	void addMesh(Mesh& mesh, Material& material);

	/**
	* Add a collection of meshes to a model with a collection of materials.
	*/
	void addMeshes(MeshCollection& meshes, MaterialCollection& materials);

	/**
	* Add a collection of meshes to a model with the same material for all.
	*/
	void addMeshes(MeshCollection& meshes, Material& material);

	/**
	* Change the material of meshes that uses this material ID. 
	*/
	void changeMaterial(int materialId, Material& newMaterial);

private:
	std::vector<MeshMaterial> meshMaterials;
};

