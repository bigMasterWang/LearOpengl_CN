#version 460 core
layout(location = 0) in vec3 in_pos3;
layout(location = 1) in vec3 in_color3;
layout(location = 2) in vec2 in_texture;

out vec3 my_color;
out vec2 my_texture;

uniform float offset_x;

void main()
{
	gl_Position = vec4(in_pos3.x, in_pos3.y, in_pos3.z, 1.0);
	// my_color = in_color3;
	my_color = vec3(in_color3.x, in_color3.y, in_color3.z);
	my_texture = in_texture;
};