#version 460 core
layout(location = 0) out vec3 frame_texture;
layout(location = 1) out vec3 normal_texture;
layout(location = 2) out vec4 position_specular_texture;


out vec4 FragColor;


in VS_OUT{
	vec3 frag_pos;
	vec3 normal;
} fs_in;
in vec2 TexCoords;
uniform sampler2D texture_diffuse1;


void main()
{
	frame_texture = texture(texture_diffuse1, TexCoords).rgb;
	normal_texture = normalize(fs_in.normal);
	position_specular_texture.rgb = fs_in.frag_pos;

}