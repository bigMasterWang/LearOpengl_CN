#version 460 core
out vec4 fragment_color;
in vec3 my_color;
void main()
{
	fragment_color = vec4(my_color.x, my_color.y, my_color.z, 1.0f);
};
