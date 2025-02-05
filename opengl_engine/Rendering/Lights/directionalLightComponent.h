#pragma once
#include "lightComponent.h"
#include <Maths/Vector3.h>

/** Directional Light Component
* Component for a directional light.
* This component doesn't use the transform of the Entity.
*/
class DirectionalLightComponent : public LightComponent
{
public:
	/**
	* Initialize the directional light.
	* @param	lightColor_			The color of the directional light.
	* @param	direction_			The direction of the directional light.
	* @param	ambientStrength_	The ambient strength of the directional light.
	* @param	diffuseStrength_	The diffuse strength of the directional light.
	*/
	void initialize(Color lightColor_, Vector3 direction_, float ambientStrength_ = 0.1f, float diffuseStrength_ = 0.5f);

	/** Apply the directional light to the lit shader. */
	void useLight(Shader& litShader, int lightIndex) override;


	void setDirection(Vector3 newDirection);

	Vector3 getDirection();

protected:
	Vector3 direction{ Vector3::unitX };
};

