#version 460 core
layout(location = 0) in vec3 in_pos3;
layout(location = 1) in vec3 in_color3;
out vec3 my_color;

uniform float offset_x;

void main()
{
	gl_Position = vec4(in_pos3.x + offset_x, in_pos3.y, in_pos3.z, 1.0);
	my_color = in_color3;
	my_color = vec3(in_pos3.x + offset_x, in_pos3.y, in_pos3.z);
};
