#include "spotLight.h"

SpotLight::SpotLight() : Light()
{
}

void SpotLight::load(Color lightColor_, Vector3 position_, Vector3 direction_, 
	float ambientStrength_, float diffuseStrength_, float cutOff_, float outerCutOff_, 
	float constant_, float linear_, float quadratic_)
{
	position = position_;
	direction = direction_;

	constant = constant_;
	linear = linear_;
	quadratic = quadratic_;

	cutOff = cutOff_;
	outerCutOff = outerCutOff_;

	lightColor = lightColor_;
	ambientStrength = ambientStrength_;
	diffuseStrength = diffuseStrength_;

	lightType = OldLightType::OldSpotLight;
	loaded = true;
}


void SpotLight::use(Shader& litShader, int lightIndex)
{
	if (!loaded) return;

	litShader.setVec3("spotLights[" + std::to_string(lightIndex) + "].position", position);
	litShader.setVec3("spotLights[" + std::to_string(lightIndex) + "].direction", direction);

	litShader.setVec3("spotLights[" + std::to_string(lightIndex) + "].ambient", off ? Vector3::zero : lightColor.toVector() * ambientStrength);
	litShader.setVec3("spotLights[" + std::to_string(lightIndex) + "].diffuse", off ? Vector3::zero : lightColor.toVector() * diffuseStrength);
	Color spec_color = Color::white;
	litShader.setVec3("spotLights[" + std::to_string(lightIndex) + "].specular", off ? Vector3::zero : spec_color.toVector());

	litShader.setFloat("spotLights[" + std::to_string(lightIndex) + "].cutOff", cutOff);
	litShader.setFloat("spotLights[" + std::to_string(lightIndex) + "].outerCutOff", outerCutOff);

	litShader.setFloat("spotLights[" + std::to_string(lightIndex) + "].constant", constant);
	litShader.setFloat("spotLights[" + std::to_string(lightIndex) + "].linear", linear);
	litShader.setFloat("spotLights[" + std::to_string(lightIndex) + "].quadratic", quadratic);
}
