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

	void addMesh(Mesh* mesh, std::shared_ptr<Material> material);

private:
	std::unordered_map<std::shared_ptr<Material>, std::vector<Mesh*>> meshMaterials;
};

