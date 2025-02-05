#include "directionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
}

void DirectionalLight::load(Color lightColor_, Vector3 direction_, float ambientStrength_, float diffuseStrength_)
{
	direction = direction_;

	lightColor = lightColor_;
	ambientStrength = ambientStrength_;
	diffuseStrength = diffuseStrength_;

	lightType = OldLightType::OldDirectionalLight;
	loaded = true;
}


void DirectionalLight::use(Shader& litShader, int lightIndex)
{
	if (!loaded) return;

	litShader.setVec3("dirLight.direction", direction);

	litShader.setVec3("dirLight.ambient", off ? Vector3::zero : lightColor.toVector() * ambientStrength);
	litShader.setVec3("dirLight.diffuse", off ? Vector3::zero : lightColor.toVector() * diffuseStrength);
	Color spec_color = Color::white;
	litShader.setVec3("dirLight.specular", off ? Vector3::zero : spec_color.toVector());
}
