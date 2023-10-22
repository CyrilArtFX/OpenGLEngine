#version 330 core

out vec4 FragColor;

in vec3 tFragPos;
in vec3 tNormal;
in vec2 tTexCoord;
in vec3 tLightPos;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	//  ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	//  diffuse
	vec3 norm = normalize(tNormal);
	vec3 lightDir = normalize(tLightPos - tFragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	//  specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(-tFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;

	//  result
	vec3 lightingResult = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(lightingResult, 1.0f);



	/*FragColor = mix(texture(texture1, tTexCoord), texture(texture2, tTexCoord), 0.2f);*/
}