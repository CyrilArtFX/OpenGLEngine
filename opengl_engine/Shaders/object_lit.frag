#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

in vec3 tFragPos;
in vec3 tNormal;
in vec2 tTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
	//  ambient
	vec3 ambient = light.ambient * material.ambient;

	//  diffuse
	vec3 norm = normalize(tNormal);
	vec3 lightDir = normalize(light.position - tFragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//  specular
	vec3 viewDir = normalize(viewPos - tFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	//  result
	vec3 lightingResult = ambient + diffuse + specular;
	FragColor = vec4(lightingResult, 1.0f);



	/*FragColor = mix(texture(texture1, tTexCoord), texture(texture2, tTexCoord), 0.2f);*/
}