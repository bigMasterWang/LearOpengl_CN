#version 460 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormals;
layout(location = 2) in vec2 aTexcoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 TexCoords;

out VS_OUT{
	vec3 frag_pos;
	vec3 normal;
} vs_out;

void main()
{
	vs_out.frag_pos = vec3(model * vec4(position, 1.0));
	vs_out.normal = transpose(inverse(mat3(model))) * aNormals;
	TexCoords = aTexcoords;
	gl_Position = projection * view * model * vec4(position, 1.0f);
}
