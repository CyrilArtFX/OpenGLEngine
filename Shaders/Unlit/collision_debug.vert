#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform bool renderLine;
uniform vec3 linePointOffset;

void main()
{
	if(renderLine == true)
	{
		gl_Position = vec4(aPos * linePointOffset, 1.0f) * model * view * projection;
	}
	else
	{
		gl_Position = vec4(aPos, 1.0f) * model * view * projection;
	}
}