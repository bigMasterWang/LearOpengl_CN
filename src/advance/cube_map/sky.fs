#version 460 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube sky_texture;


void main()
{
    FragColor = texture(sky_texture, TexCoords);
} 