#include "spotLightComponent.h"
#include <ServiceLocator/locator.h>

void SpotLightComponent::initialize(Color lightColor_, Vector3 offset_, Vector3 direction_, float ambientStrength_, float diffuseStrength_, float cutOff_, float outerCutOff_, float constant_, float linear_, float quadratic_)
{
	direction = direction_;
	cutOff = cutOff_;
	outerCutOff = outerCutOff_;

	offset = offset_;
	constant = constant_;
	linear = linear_;
	quadratic = quadratic_;

	lightColor = lightColor_;
	ambientStrength = ambientStrength_;
	diffuseStrength = diffuseStrength_;

	lightType = LightType::ESpotLight;
	initialized = true;

	initializePosition();

	Locator::getRenderer().AddLight(this);
}

void SpotLightComponent::useLight(Shader& litShader, int lightIndex)
{
	if (!initialized) return;

	std::string light_index = std::to_string(lightIndex);

	litShader.setVec3("spotLights[" + light_index + "].position", position);
	litShader.setVec3("spotLights[" + light_index + "].direction", direction);

	litShader.setVec3("spotLights[" + light_index + "].ambient", active ? lightColor.toVector() * ambientStrength : Vector3::zero);
	litShader.setVec3("spotLights[" + light_index + "].diffuse", active ? lightColor.toVector() * diffuseStrength : Vector3::zero);
	Color spec_color = useColorToSpecular ? lightColor : Color::white;
	litShader.setVec3("spotLights[" + light_index + "].specular", active ? spec_color.toVector() : Vector3::zero);

	litShader.setFloat("spotLights[" + light_index + "].cutOff", cutOff);
	litShader.setFloat("spotLights[" + light_index + "].outerCutOff", outerCutOff);

	litShader.setFloat("spotLights[" + light_index + "].constant", constant);
	litShader.setFloat("spotLights[" + light_index + "].linear", linear);
	litShader.setFloat("spotLights[" + light_index + "].quadratic", quadratic);
}

void SpotLightComponent::setUseDiffColorToSpecColor(bool value)
{
	useColorToSpecular = value;
}


void SpotLightComponent::setDirection(Vector3 newDirection)
{
	direction = newDirection;
}

void SpotLightComponent::setCutOff(float newCutOff)
{
	cutOff = newCutOff;
}

void SpotLightComponent::setOuterCutOff(float newOuterCutOff)
{
	outerCutOff = newOuterCutOff;
}

Vector3 SpotLightComponent::getDirection()
{
	return direction;
}

float SpotLightComponent::getCutOff()
{
	return cutOff;
}

float SpotLightComponent::getOuterCutOff()
{
	return outerCutOff;
}
