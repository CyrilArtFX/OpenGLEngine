#include "SpotLight.h"

SpotLight::SpotLight(LightType lightType_, Color lightColor_, Vector3 position_, Vector3 direction_, 
	float ambientStrength_, float diffuseStrength_, float cutOff_, float outerCutOff_, 
	float constant_, float linear_, float quadratic_) : position(position_), direction(direction_),
	constant(constant_), linear(linear_), quadratic(quadratic_),
	cutOff(cutOff_), outerCutOff(outerCutOff_), Light(lightType_)
{
	lightColor = lightColor_;
	ambientStrength = ambientStrength_;
	diffuseStrength = diffuseStrength_;
}


void SpotLight::use(Shader& litShader, int lightIndex)
{
	litShader.setVec3("spotLights[" + std::to_string(lightIndex) + "].position", position);
	litShader.setVec3("spotLights[" + std::to_string(lightIndex) + "].direction", direction);

	litShader.setVec3("spotLights[" + std::to_string(lightIndex) + "].ambient", lightColor.toVector() * ambientStrength);
	litShader.setVec3("spotLights[" + std::to_string(lightIndex) + "].diffuse", lightColor.toVector() * diffuseStrength);
	Color spec_color = Color::white;
	litShader.setVec3("spotLights[" + std::to_string(lightIndex) + "].specular", spec_color.toVector());

	litShader.setFloat("spotLights[" + std::to_string(lightIndex) + "].cutOff", cutOff);
	litShader.setFloat("spotLights[" + std::to_string(lightIndex) + "].outerCutOff", outerCutOff);

	litShader.setFloat("spotLights[" + std::to_string(lightIndex) + "].constant", constant);
	litShader.setFloat("spotLights[" + std::to_string(lightIndex) + "].linear", linear);
	litShader.setFloat("spotLights[" + std::to_string(lightIndex) + "].quadratic", quadratic);
}
