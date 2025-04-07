#pragma once
#include <ECS/component.h>
#include <Events/observer.h>
#include <Rendering/Model/model.h>
#include <Objects/transform.h>


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


	/** Set the position offset from the owner entity of this Model Renderer Component. */
	void setPosOffset(const Vector3& newPosOffset);

	/** Get the position offset from the owner entity of this Model Renderer Component. */
	Vector3 getPosOffset() const;

	/** Set the rotation offset from the owner entity of this Model Renderer Component. */
	void setRotOffset(const Quaternion& newRotOffset);

	/** Get the rotation offset from the owner entity of this Model Renderer Component. */
	Quaternion getRotOffset() const;

	/** Set the scale offset from the owner entity of this Model Renderer Component. */
	void setScaleOffset(const Vector3& newScaleOffset);

	/** Get the scale offset from the owner entity of this Model Renderer Component. */
	Vector3 getScaleOffset() const;


protected:
	virtual void registerComponent() override;
	virtual void unregisterComponent() override;

	virtual void init() override;
	virtual void exit() override;

	void onEntityMoved();
	virtual void computeMatrix();

	Model* model{ nullptr };

	Matrix4 modelMatrix{ Matrix4::identity };
	Matrix4 normalMatrix{ Matrix4::identity };
	Vector3 scale{ Vector3::one };

	Transform offset;
};

