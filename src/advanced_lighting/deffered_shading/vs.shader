#version 460 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 aTexcoords;

out vec2 TexCoords;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = vec4(position, 1.0f);
	TexCoords = aTexcoords;
}
