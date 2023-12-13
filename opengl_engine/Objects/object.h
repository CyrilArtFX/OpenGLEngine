#pragma once

#include <Rendering/Model/model.h>
#include "transform.h"

#include <vector>

class Object : public Transform
{
public:
	Object();

	void draw(Material* materialInUsage);

	void addModel(Model* model);

private:
	std::vector<Model*> models;
};

