#version 460 core
layout(location = 0) in vec3 in_pos3;
layout(location = 1) in vec2 in_texture;

out vec2 my_texture;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;


void main()
{
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_pos3.x, in_pos3.y, in_pos3.z, 1.0);
	my_texture = in_texture;
};