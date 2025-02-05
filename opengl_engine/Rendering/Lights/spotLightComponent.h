#pragma once
#include "positionBasedLight.h"

/** Spot Light Component
* Component for a spot light.
* The offset of the spot light is computed with the rotation and scale of the Entity.
*/
class SpotLightComponent : public PositionBasedLight
{
public:
	/**
	* Initialize the spot light.
	* @param	lightColor_			The color of the spot light.
	* @param	offset_				The offset of the spot light.
	* @param	ambientStrength_	The ambient strength of the spot light.
	* @param	diffuseStrength_	The diffuse strength of the spot light.
	* @param	cutOff_				The cut off angle of the spot light.
	* @param	outerCutOff_		The outer cut off angle of the spot light.
	* @param	constant_			The falloff constant value of the spot light.
	* @param	linear_				The falloff linear value of the spot light.
	* @param	quadratic_			The falloff quadratic value of the spot light.
	*/
	void initialize(Color lightColor_, Vector3 offset_, Vector3 direction_, float ambientStrength_ = 0.01f, float diffuseStrength_ = 0.7f,
		float cutOff_ = Maths::cos(Maths::toRadians(12.5f)), float outerCutOff_ = Maths::cos(Maths::toRadians(17.5f)),
		float constant_ = 1.0f, float linear_ = 0.09f, float quadratic_ = 0.032f);

	/** Apply the spot light to the lit shader. */
	void useLight(Shader& litShader, int lightIndex) override;

	/** Set the spot light use the diffuse color for the specular color (default specular color is white). */
	void setUseDiffColorToSpecColor(bool value);


	void setDirection(Vector3 newDirection);
	void setCutOff(float newCutOff);
	void setOuterCutOff(float newOuterCutOff);

	Vector3 getDirection();
	float getCutOff();
	float getOuterCutOff();

protected:
	bool useColorToSpecular{ false };

	Vector3 direction{ Vector3::unitX };

	float cutOff{ 0.0f };
	float outerCutOff{ 0.0f };
};

