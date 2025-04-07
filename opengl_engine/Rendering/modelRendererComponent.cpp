#include "modelRendererComponent.h"
#include <ECS/entity.h>
#include <ServiceLocator/locator.h>


void ModelRendererComponent::draw(Material& materialInUsage)
{
	//  we don't check useMaterial() cause the renderer should've done it already

	Shader& shader_used = materialInUsage.getShader();

	shader_used.setMatrix4("model", modelMatrix.getAsFloatPtr());
	shader_used.setMatrix4("normalMatrix", normalMatrix.getAsFloatPtr());
	shader_used.setVec3("scale", scale);

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

void ModelRendererComponent::setIgnoreOwnerTransform(bool value)
{
	ignoreOwnerTransform = value;

	computeMatrix();
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
	modelMatrix = Matrix4::identity;
	normalMatrix = Matrix4::identity;
	scale = Vector3::one;
	offset.clearTranform();


	getOwner()->onTransformUpdated.registerObserver(this, Bind_0(&ModelRendererComponent::onEntityMoved));
	offset.onTransformUpdated.registerObserver(this, Bind_0(&ModelRendererComponent::onOffsetUpdated));
	computeMatrix();
}

void ModelRendererComponent::exit()
{
	getOwner()->onTransformUpdated.unregisterObserver(this);
	offset.onTransformUpdated.unregisterObserver(this);
}

void ModelRendererComponent::onEntityMoved()
{
	computeMatrix();
}

void ModelRendererComponent::onOffsetUpdated()
{
	computeMatrix();
}

void ModelRendererComponent::computeMatrix()
{
	if (ignoreOwnerTransform)
	{
		modelMatrix = offset.getModelMatrix();
		scale = offset.getScale();
	}
	else
	{
		modelMatrix = offset.getModelMatrix() * getOwner()->getModelMatrix();
		scale = offset.getScale() * getOwner()->getScale();
	}

	normalMatrix = modelMatrix;
	normalMatrix.invert();
	normalMatrix.transpose();
}
