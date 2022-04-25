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
	vec4 world_pos = model * vec4(position, 1.0);
	vs_out.frag_pos = world_pos.xyz;
	vs_out.normal = transpose(inverse(mat3(model))) * aNormals;
	TexCoords = aTexcoords;
	// 因为这个看起来是没毛病的， 所以world_pos应该是对的
	gl_Position = projection * view * world_pos;
}
