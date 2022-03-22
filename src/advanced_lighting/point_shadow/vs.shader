#version 460 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormals;
layout(location = 2) in vec2 aTexcoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform int reverse_normals;

out VS_OUT{
	vec3 frag_pos;
	vec3 normal;
	vec2 texcoords;
} vs_out;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);

	vs_out.frag_pos = vec3(model * vec4(position, 1.0));
	if (reverse_normals == 1)
		vs_out.normal = transpose(inverse(mat3(model))) * (-1 * aNormals);
	else
		vs_out.normal = transpose(inverse(mat3(model))) * aNormals;
	vs_out.texcoords = aTexcoords;
}
