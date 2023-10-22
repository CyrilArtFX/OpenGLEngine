#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 tFragPos;
out vec3 tNormal;
out vec2 tTexCoord;
out vec3 tLightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

void main()
{
	gl_Position = vec4(aPos, 1.0f) * model * view * projection;
	tFragPos = vec3(vec4(aPos, 1.0f) * model * view);

	//  huge cost for gpu, should be done on gpu and send here with uniform
	tNormal = aNormal * mat3(transpose(inverse(model * view)));
	
	tTexCoord = aTexCoord;

	tLightPos = vec3(vec4(lightPos, 1.0f) * view);
}