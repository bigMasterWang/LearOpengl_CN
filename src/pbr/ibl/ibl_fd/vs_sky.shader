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
	mat4 rotView = mat4(mat3(view));
	vec4 clipPos = projection * rotView * vec4(in_pos3, 1.0);
	gl_Position = clipPos.xyww;
}