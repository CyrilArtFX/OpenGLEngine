#include "directionalLightComponent.h"
#include <ServiceLocator/locator.h>

void DirectionalLightComponent::initialize(Color lightColor_, Vector3 direction_, float ambientStrength_, float diffuseStrength_)
{
	direction = direction_;

	lightColor = lightColor_;
	ambientStrength = ambientStrength_;
	diffuseStrength = diffuseStrength_;

	lightType = LightType::EDirectionalLight;
	initialized = true;

	Locator::getRenderer().AddLight(this);
}

void DirectionalLightComponent::useLight(Shader& litShader, int lightIndex)
{
	if (!initialized) return;

	litShader.setVec3("dirLight.direction", direction);

	litShader.setVec3("dirLight.ambient", active ? lightColor.toVector() * ambientStrength : Vector3::zero);
	litShader.setVec3("dirLight.diffuse", active ? lightColor.toVector() * diffuseStrength : Vector3::zero);
	Color spec_color = Color::white;
	litShader.setVec3("dirLight.specular", active ? spec_color.toVector() : Vector3::zero);
}

void DirectionalLightComponent::setDirection(Vector3 newDirection)
{
	direction = newDirection;
}

Vector3 DirectionalLightComponent::getDirection()
{
	return direction;
}
