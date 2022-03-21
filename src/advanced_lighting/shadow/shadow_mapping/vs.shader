//#version 460 core
//layout(location = 0) in vec2 aPos;
//layout(location = 1) in vec2 aTexCoords;
//
//
//uniform mat4 projection;
//uniform mat4 view;
//uniform mat4 model;
//
//out vec2 TexCoords;
//
//void main()
//{
//	TexCoords = aTexCoords;
//	gl_Position = projection * view * model * vec4(aPos.x, aPos.y, 0.0, 1.0);
//	// gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
//}
#version 460 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormals;
layout(location = 2) in vec2 aTexcoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 light_space;

out vec2 TexCoords;

out VS_OUT{
	vec3 frag_pos;
	vec3 normal;
	vec2 texcoords;
	vec4 light_space_frag_pos;
} vs_out;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);

	vs_out.frag_pos = vec3(model * vec4(position, 1.0));
	vs_out.normal = transpose(inverse(mat3(model))) * aNormals;
	vs_out.texcoords = aTexcoords;
	vs_out.light_space_frag_pos = light_space * vec4(vs_out.frag_pos, 1.0);

	TexCoords = aTexcoords;

}
