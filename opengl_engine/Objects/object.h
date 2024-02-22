#pragma once

#include <Rendering/Model/model.h>
#include "transform.h"

#include <vector>

class Object : public Transform
{
public:
	Object();

	void draw(Material* materialInUsage);
	void update(float dt);

	void addModel(Model* model);

	virtual void load() {}
	virtual void updateObject(float dt) {}

private:
	std::vector<Model*> models;
};

