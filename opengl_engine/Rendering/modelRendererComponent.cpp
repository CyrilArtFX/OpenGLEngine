#include "modelRendererComponent.h"
#include <ECS/entity.h>
#include <ServiceLocator/locator.h>


void ModelRendererComponent::draw(Material& materialInUsage)
{
	//  we don't check useMaterial() cause the renderer should've done it already

	Shader& shader_used = materialInUsage.getShader();
	Transform* owner_transform = getOwner();

	shader_used.setMatrix4("model", owner_transform->getModelMatrix().getAsFloatPtr());
	shader_used.setMatrix4("normalMatrix", owner_transform->getNormalMatrix().getAsFloatPtr());
	shader_used.setVec3("scale", owner_transform->getScale());

	model->draw(materialInUsage);
}


void ModelRendererComponent::setModel(Model* newModel)
{
	model = newModel;
}

Model& ModelRendererComponent::getModel()
{
	return *model;
}

bool ModelRendererComponent::useMaterial(Material& material)
{
	if (!model) return false; //  this will also allow the rendering sequence to not call draw() on this component if it doesn't have a model

	return model->useMaterial(material);
}




void ModelRendererComponent::registerComponent()
{
	Locator::getRenderer().AddModelRenderer(this);
}

void ModelRendererComponent::unregisterComponent()
{
	Locator::getRenderer().RemoveModelRenderer(this);
}

void ModelRendererComponent::init()
{
	//  reset the values in case this component was used before (the component manager is a memory pool)
	model = nullptr;
}
