#version 330 core

layout (location = 0) in vec2 vertex; //  vertex pos

out VS_OUT{
	vec2 TexCoords;
	flat int index;
} vs_out;

uniform mat4 projection;
uniform mat4 textTransforms[200];

void main()
{
	gl_Position = vec4(vertex.xy, 0.0f, 1.0f) * textTransforms[gl_InstanceID] * projection;

	vs_out.index = gl_InstanceID;
	vs_out.TexCoords.x = vertex.x;
	vs_out.TexCoords.y = 1.0f - vertex.y;
}