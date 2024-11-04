#version 330 core

layout (location = 0) in vec2 vertex; //  vertex pos

out VS_OUT{
	vec2 TexCoords;
	flat int index;
} vs_out;

uniform mat4 projection;
uniform vec4 textPosScales[400]; // vec2 pos (xy) & vec2 scale (zw)

void main()
{
	gl_Position = projection * vec4((vertex.xy * textPosScales[gl_InstanceID].zw) + textPosScales[gl_InstanceID].xy, 0.0f, 1.0f);

	vs_out.index = gl_InstanceID;
	vs_out.TexCoords.x = vertex.x;
	vs_out.TexCoords.y = 1.0f - vertex.y;
}