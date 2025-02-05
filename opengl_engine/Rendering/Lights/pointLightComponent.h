#pragma once
#include "positionBasedLight.h"

/** Point Light Component
* Component for a point light.
* The offset of the point light is computed with the rotation and scale of the Entity.
*/
class PointLightComponent : public PositionBasedLight
{
public:
	/**
	* Initialize the point light.
	* @param	lightColor_			The color of the point light.
	* @param	offset_				The offset of the point light.
	* @param	ambientStrength_	The ambient strength of the point light.
	* @param	diffuseStrength_	The diffuse strength of the point light.
	* @param	constant_			The falloff constant value of the point light.
	* @param	linear_				The falloff linear value of the point light.
	* @param	quadratic_			The falloff quadratic value of the point light.
	*/
	void initialize(Color lightColor_, Vector3 offset_, float ambientStrength_ = 0.01f, float diffuseStrength_ = 0.7f,
		float constant_ = 1.0f, float linear_ = 0.09f, float quadratic_ = 0.032f);

	/** Apply the point light to the lit shader. */
	void useLight(Shader& litShader, int lightIndex) override;

	/** Set the point light use the diffuse color for the specular color (default specular color is white). */
	void setUseDiffColorToSpecColor(bool value);

protected:
	bool useColorToSpecular{ false };
};

