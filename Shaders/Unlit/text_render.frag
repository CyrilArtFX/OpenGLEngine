#version 330 core


in VS_OUT{
	vec2 TexCoords;
	flat int index;
} fs_in;

out vec4 color;

uniform sampler2DArray text;
uniform int letterMap[200];
uniform vec3 textColor;

void main()
{
	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(text, vec3(fs_in.TexCoords, letterMap[fs_in.index])).r);
	color = vec4(textColor, 1.0f) * sampled;
}
