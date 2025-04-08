#pragma once
#include <ECS/component.h>
#include <Events/observer.h>
#include <Rendering/Model/model.h>
#include <Core/transform.h>


/** Model Renderer Component
* A component that will render a Model.
*/
class ModelRendererComponent : public Component, public Observer
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

	/**
	* Set the ignore owner transform value of this component.
	* If the Model Renderer Component ignore its owner transform, it will only use its offset transform.
	* @param	value	The ignore owner transform value to set.
	*/
	void setIgnoreOwnerTransform(bool value);

	/**
	* Get the ignore owner transform value of this component.
	* @return			The ignore owner transform value of this component.
	*/
	bool getIgnoreOwnerTransform() const { return ignoreOwnerTransform; }

	/** The transform offset of this Model Renderer Component. */
	Transform offset;


protected:
	virtual void registerComponent() override;
	virtual void unregisterComponent() override;

	virtual void init() override;
	virtual void exit() override;

	void onEntityMoved();
	void onOffsetUpdated();
	virtual void computeMatrix();

	Model* model{ nullptr };

	bool ignoreOwnerTransform{ false };

	Matrix4 modelMatrix{ Matrix4::identity };
	Matrix4 normalMatrix{ Matrix4::identity };
	Vector3 scale{ Vector3::one };
};

