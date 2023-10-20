#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	float ambientStrength = 0.2f;
	vec3 ambient = ambientStrength * lightColor;

	/*FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2f);*/
	vec3 lightingResult = ambient * objectColor;
	FragColor = vec4(lightingResult, 1.0f);
}