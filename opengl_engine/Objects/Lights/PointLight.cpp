#include "PointLight.h"

PointLight::PointLight(LightType lightType_, Color lightColor_, Vector3 position_, float ambientStrength_, float diffuseStrength_,
	float constant_, float linear_, float quadratic_) : position(position_), constant(constant_), linear(linear_), quadratic(quadratic_), Light(lightType_)
{
	lightColor = lightColor_;
	ambientStrength = ambientStrength_;
	diffuseStrength = diffuseStrength_;
}


void PointLight::use(Shader& litShader, int lightIndex)
{
	litShader.setVec3("pointLights[" + std::to_string(lightIndex) + "].position", position);

	litShader.setVec3("pointLights[" + std::to_string(lightIndex) + "].ambient", lightColor.toVector() * ambientStrength); 
	litShader.setVec3("pointLights[" + std::to_string(lightIndex) + "].diffuse", lightColor.toVector() * diffuseStrength);
	Color spec_color = Color::white;
	litShader.setVec3("pointLights[" + std::to_string(lightIndex) + "].specular", spec_color.toVector()); 

	litShader.setFloat("pointLights[" + std::to_string(lightIndex) + "].constant", constant);
	litShader.setFloat("pointLights[" + std::to_string(lightIndex) + "].linear", linear);
	litShader.setFloat("pointLights[" + std::to_string(lightIndex) + "].quadratic", quadratic);
}