#version 460 core

out vec4 fragment_color;

in vec2 my_texture;


uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	fragment_color = mix(texture(texture1, my_texture), texture(texture2, my_texture), 0.5);
};
