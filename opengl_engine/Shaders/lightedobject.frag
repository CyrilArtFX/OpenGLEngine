#version 330 core

out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	float ambientStrength = 0.2f;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	vec3 lightingResult = (ambient + diffuse) * objectColor;
	FragColor = vec4(lightingResult, 1.0f);



	/*FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2f);*/
}