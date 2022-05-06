#version 460 core
layout(location = 0) in vec3 in_pos3;
layout(location = 1) in vec2 in_texture;
layout(location = 2) in vec3 fragment_normalize;
out vec3 localPos;

uniform mat4 projection;
uniform mat4 view;
// uniform mat4 model; model没用，这个是建立在原点上的

void main()
{
	localPos = in_pos3;
	gl_Position = projection * view * vec4(in_pos3, 1.0);
}