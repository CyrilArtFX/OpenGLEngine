#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = vec4(aPos, 1.0f) * model * view * projection;
	fragPos = vec3(vec4(aPos, 1.0f) * model);

	//  huge cost for gpu, should be done on gpu and send here with uniform
	normal = aNormal * mat3(transpose(inverse(model)));
	
	texCoord = aTexCoord;
}