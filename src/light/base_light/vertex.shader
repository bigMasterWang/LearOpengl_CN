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

//�������������ת����, û��ƽ�ƺ�����, �������㷨��������ת
uniform mat4 model_scale_matrix;


void main()
{
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_pos3.x, in_pos3.y, in_pos3.z, 1.0);
	my_texture = in_texture;

	//Ƭ�η���ҲҪ���������ƶ�
	// my_fragment_normalize = vec3(model_scale_matrix * vec4(fragment_normalize, 0.0));
	my_fragment_normalize = transpose(inverse(mat3(model_matrix))) * fragment_normalize;
	// Ƭ�ε�λ��Ҫ������������ϵ�µ�
	my_fragment_pos = vec3(model_matrix * vec4(in_pos3, 1.0));
};