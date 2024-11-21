#version 330 core

layout (location = 0) in vec2 vertex; //  vertex pos

out vec2 TexCoords;

uniform mat4 projection;
uniform vec4 spritePosScale; // vec2 pos (xy) & vec2 scale (zw)

void main()
{
	gl_Position = projection * vec4((vertex.xy * spritePosScale.zw) + spritePosScale.xy, 0.0f, 1.0f);
	
	TexCoords.x = vertex.x;
	TexCoords.y = 1.0f - vertex.y;
}