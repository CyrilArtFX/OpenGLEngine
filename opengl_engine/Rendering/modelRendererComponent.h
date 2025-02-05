#pragma once
#include <ECS/component.h>
#include <Rendering/Model/model.h>

class ModelRendererComponent : public Component
{
public:
	/**
	* Draw the model of this Model Renderer Component.
	* This function is called by the rendering sequence, do not call it manually.
	* @param	materialInUsage		The material currently in use in the rendering sequence.
	*/
	void draw(Material& materialInUsage);


	/**
	* Set the model that this component will render.
	* @param	newModel	The model to render with this component.
	*/
	void setModel(Model* newModel);

	/**
	* Get the model rendered by this component.
	* @return	The model rendered by this component.
	*/
	Model& getModel();

	/**
	* Know if this Model Renderer Component uses a specific material.
	* @param	material	The material to test.
	* @return				True if this component uses this material.
	*/
	bool useMaterial(Material& material);

protected:
	virtual void registerComponent() override;
	virtual void unregisterComponent() override;

	Model* model;
};

