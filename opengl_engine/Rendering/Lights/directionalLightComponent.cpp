#include "directionalLightComponent.h"
#include <ServiceLocator/locator.h>

void DirectionalLightComponent::useLight(Shader& litShader, int lightIndex)
{
	litShader.setVec3("dirLight.direction", direction);

	litShader.setVec3("dirLight.ambient", lightColor.toVector() * ambientStrength);
	litShader.setVec3("dirLight.diffuse", lightColor.toVector() * diffuseStrength);
	Color spec_color = Color::white;
	litShader.setVec3("dirLight.specular", spec_color.toVector());
}

void DirectionalLightComponent::init()
{
	lightType = LightType::EDirectionalLight;

	Locator::getRenderer().AddLight(this);
}

void DirectionalLightComponent::setDirection(Vector3 newDirection)
{
	direction = newDirection;
}

Vector3 DirectionalLightComponent::getDirection() const
{
	return direction;
}
