#version 460 core

out vec4 fragment_color;

in vec2 my_texture;


uniform sampler2D texture1;
uniform sampler2D texture2;


uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	// fragment_color = mix(texture(texture1, my_texture), texture(texture2, my_texture), 0.5);
	fragment_color = vec4(lightColor * objectColor, 1.0) * mix(texture(texture1, my_texture), texture(texture2, my_texture), 0.5);
};




