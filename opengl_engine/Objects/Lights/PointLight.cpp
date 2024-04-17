#include "pointLight.h"

PointLight::PointLight() : Light()
{
}

void PointLight::load(Color lightColor_, Vector3 position_, float ambientStrength_, float diffuseStrength_,
	float constant_, float linear_, float quadratic_)
{
	position = position_;
	
	constant = constant_;
	linear = linear_;
	quadratic = quadratic_;

	lightColor = lightColor_;
	ambientStrength = ambientStrength_;
	diffuseStrength = diffuseStrength_;

	lightType = LightType::EPointLight;
	loaded = true;
}


void PointLight::use(Shader& litShader, int lightIndex)
{
	if (!loaded) return;

	litShader.setVec3("pointLights[" + std::to_string(lightIndex) + "].position", position);

	litShader.setVec3("pointLights[" + std::to_string(lightIndex) + "].ambient", off ? Vector3::zero : lightColor.toVector() * ambientStrength); 
	litShader.setVec3("pointLights[" + std::to_string(lightIndex) + "].diffuse", off ? Vector3::zero : lightColor.toVector() * diffuseStrength);
	Color spec_color = useColorToSpecular ? lightColor : Color::white;
	litShader.setVec3("pointLights[" + std::to_string(lightIndex) + "].specular", off ? Vector3::zero : spec_color.toVector());

	litShader.setFloat("pointLights[" + std::to_string(lightIndex) + "].constant", constant);
	litShader.setFloat("pointLights[" + std::to_string(lightIndex) + "].linear", linear);
	litShader.setFloat("pointLights[" + std::to_string(lightIndex) + "].quadratic", quadratic);
}
