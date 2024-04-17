#include "object.h"

Object::Object() : Transform()
{
}


void Object::draw(Material* materialInUsage)
{
	materialInUsage->getShader().setMatrix4("model", getModelMatrix().getAsFloatPtr());
	materialInUsage->getShader().setMatrix4("normalMatrix", getNormalMatrix().getAsFloatPtr());
	materialInUsage->getShader().setVec3("scale", getScale());

	for (auto model : models)
	{
		model->draw(materialInUsage);
	}
}

void Object::update(float dt)
{
	updateObject(dt);
}


void Object::addModel(Model* model)
{
	models.push_back(model);
}

Model& Object::getModel(int index)
{
	return *models[index];
}
