#include "pointLightComponent.h"
#include <ServiceLocator/locator.h>

void PointLightComponent::initialize(Color lightColor_, Vector3 offset_, float ambientStrength_, float diffuseStrength_, float constant_, float linear_, float quadratic_)
{
	offset = offset_;
	constant = constant_;
	linear = linear_;
	quadratic = quadratic_;

	lightColor = lightColor_;
	ambientStrength = ambientStrength_;
	diffuseStrength = diffuseStrength_;

	lightType = LightType::EPointLight;
	initialized = true;

	initializePosition();

	Locator::getRenderer().AddLight(this);
}

void PointLightComponent::useLight(Shader& litShader, int lightIndex)
{
	if (!initialized) return;

	std::string light_index = std::to_string(lightIndex);

	litShader.setVec3("pointLights[" + light_index + "].position", position);

	litShader.setVec3("pointLights[" + light_index + "].ambient", active ? lightColor.toVector() * ambientStrength : Vector3::zero);
	litShader.setVec3("pointLights[" + light_index + "].diffuse", active ? lightColor.toVector() * diffuseStrength : Vector3::zero);
	Color spec_color = useColorToSpecular ? lightColor : Color::white;
	litShader.setVec3("pointLights[" + light_index + "].specular", active ? spec_color.toVector() : Vector3::zero);

	litShader.setFloat("pointLights[" + light_index + "].constant", constant);
	litShader.setFloat("pointLights[" + light_index + "].linear", linear);
	litShader.setFloat("pointLights[" + light_index + "].quadratic", quadratic);
}

void PointLightComponent::setUseDiffColorToSpecColor(bool value)
{
	useColorToSpecular = value;
}
