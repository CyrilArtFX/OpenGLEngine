#version 330 core

layout (location = 0) in vec2 vertex; //  vertex pos

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 spriteTransform;

void main()
{
	gl_Position = vec4(vertex.xy, 0.0f, 1.0f) * spriteTransform * projection;
	
	TexCoords.x = vertex.x;
	TexCoords.y = 1.0f - vertex.y;
}