#pragma once

#include <Rendering/Model/model.h>
#include "transform.h"

#include <vector>

class Object : public Transform
{
public:
	Object();

	void draw(std::shared_ptr<Material> materialInUsage);

	void addModel(std::weak_ptr<Model> model);

private:
	std::vector<std::shared_ptr<Model>> models;
};

