#version 460 core
layout(location = 0) in vec3 in_pos3;
layout(location = 1) in vec2 in_texture;
layout(location = 2) in vec3 fragment_normalize;


out vec2 my_texture;
out vec3 my_fragment_normalize;
out vec3 my_fragment_pos;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;


void main()
{
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_pos3.x, in_pos3.y, in_pos3.z, 1.0);
	my_texture = in_texture;

	//片段法线也要跟随物体移动
	my_fragment_normalize = transpose(inverse(mat3(model_matrix))) * fragment_normalize;
	// 片段的位置要计算世界坐标系下的
	my_fragment_pos = vec3(model_matrix * vec4(in_pos3, 1.0));
};