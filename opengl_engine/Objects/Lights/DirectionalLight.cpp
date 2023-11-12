#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(LightType lightType_, Color lightColor_, Vector3 direction_, float ambientStrength_, float diffuseStrength_) :
	direction(direction_), Light(lightType_)
{
	lightColor = lightColor_;
	ambientStrength = ambientStrength_;
	diffuseStrength = diffuseStrength_;
}


void DirectionalLight::use(Shader& litShader, int lightIndex)
{
	litShader.setVec3("dirLight.direction", direction);

	litShader.setVec3("dirLight.ambient", lightColor.toVector() * ambientStrength);
	litShader.setVec3("dirLight.diffuse", lightColor.toVector() * diffuseStrength);
	Color spec_color = Color::white;
	litShader.setVec3("dirLight.specular", spec_color.toVector());
}
